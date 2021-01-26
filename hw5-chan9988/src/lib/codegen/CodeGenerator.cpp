#include "codegen/CodeGenerator.hpp"
#include "visitor/AstNodeInclude.hpp"

#include <cassert>
#include <cstdarg>
#include <cstdio>

CodeGenerator::CodeGenerator(const char *in_file_name, const char *out_file_name, SymbolManager *symbol_manager) 
    : in_file_name(in_file_name), symbol_manager(symbol_manager) {
    this->out_fp = fopen(out_file_name, "w");
    assert(this->out_fp != NULL && "fopen() fails");
}

CodeGenerator::~CodeGenerator() {
    fclose(this->out_fp);
}

void CodeGenerator::dumpInstrs(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(this->out_fp, format, args);
    va_end(args);
}

void CodeGenerator::visit(ProgramNode &p_program) {
    // Reconstruct the hash table for looking up the symbol entry
    // Hint: Use symbol_manager->lookup(symbol_name) to get the symbol entry.
    symbol_manager->reconstructHashTableFromSymbolTable(p_program.getSymbolTable());

    // Generate RISC-V instructions for program header
    dumpInstrs("%s\"%s\"%s%s", 
        "   .file ", this->in_file_name, "\n",
        "   .option nopic\n"
    );

    p_program.visit_decl_func(*this);

    dumpInstrs(".section    .text\n");
    dumpInstrs("    .align 2\n");
    dumpInstrs("    .globl main\n");
    dumpInstrs("    .type main, @function\n");
    dumpInstrs("main:\n");
    // function prologue
    dumpInstrs("    addi sp, sp, -128\n");
    dumpInstrs("    sw ra, 124(sp)\n");
    dumpInstrs("    sw s0, 120(sp)\n");
    dumpInstrs("    addi s0, sp, 128\n");

    p_program.visitcom(*this);
    // function epilogue
    dumpInstrs("    lw ra, 124(sp)\n");
    dumpInstrs("    lw s0, 120(sp)\n");
    dumpInstrs("    addi sp, sp, 128\n");
    dumpInstrs("    jr ra\n");
    dumpInstrs("    .size main, .-main\n");

    for(int i=0;i<la.size();i++){
        dumpInstrs("%s\n",la[i].c_str());
    }

    // Remove the entries in the hash table
    symbol_manager->removeSymbolsFromHashTable(p_program.getSymbolTable());
}

void CodeGenerator::visit(DeclNode &p_decl) {
    p_decl.visitChildNodes(*this);
}

void CodeGenerator::visit(VariableNode &p_variable) {
    auto *entry = symbol_manager->lookup(p_variable.getName());
    if(entry!=NULL&&entry->getKind() == SymbolEntry::KindEnum::kVariableKind && entry->getLevel()==0 ){
        dumpInstrs(".comm %s, %d, %d\n",p_variable.getName().c_str(),4,4);
    }
    else if(entry!=NULL&&entry->getKind() == SymbolEntry::KindEnum::kConstantKind && entry->getLevel()==0 ){
        dumpInstrs(".section    .rodata\n");
        dumpInstrs("    .align 2\n");
        dumpInstrs("    .globl %s\n",p_variable.getName().c_str());
        dumpInstrs("    .type %s, @object\n",p_variable.getName().c_str());
        dumpInstrs("%s:\n",p_variable.getName().c_str());
        dumpInstrs("    .word %s\n",p_variable.getConstantPtr()->getConstantValueCString());
    }
    else if(p_variable.getTypePtr()->isReal()){
        add_var(p_variable.getName());
        offset-=4;
        for(int i=0;i<dec_var.size();i++){
            if(dec_var[i].first==p_variable.getName()){
                return;
            }
        }
        dec_var.push_back(make_pair(p_variable.getName(),1));
    }
    else if(p_variable.getTypePtr()->isString()){
        for(int i=0;i<dec_var.size();i++){
            if(dec_var[i].first==p_variable.getName()){
                return;
            }
        }
        dec_var.push_back(make_pair(p_variable.getName(),2));
    }
    else if(p_variable.getTypePtr()->isBool()){
        add_var(p_variable.getName());
        offset-=4;
        for(int i=0;i<dec_var.size();i++){
            if(dec_var[i].first==p_variable.getName()){
                return;
            }
        }
        dec_var.push_back(make_pair(p_variable.getName(),3));
    }
    else{
        if(p_variable.getConstantPtr()==NULL){

            add_var(p_variable.getName());
            //auto t=find_ind(p_variable.getName());
            int sum=1;
            for (auto dimension : p_variable.getTypePtr()->getDimensions()){
                sum*=dimension;
                add_ind(p_variable.getName(),dimension);
                //dumpInstrs("%d  123123123\n",dimension);
                //dumpInstrs("%d 1111111\n",t.size());
            }
            //auto k=find_ind(p_variable.getName());
            //dumpInstrs("%d 1111111\n",k.size());
            offset-=4*sum;
        }
        else{
            add_var(p_variable.getName());
            offset-=4;
            dumpInstrs("    addi t0, s0, %d\n",find_var(p_variable.getName()));
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    sw t0, 0(sp)\n");
            p_variable.visitChildNodes(*this);
            dumpInstrs("    lw t0, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    lw t1, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    sw t0, 0(t1)\n");
        }
        
    }
    
}

void CodeGenerator::visit(ConstantValueNode &p_constant_value) {
    //dumpInstrs("    .word %s\n",p_constant_value.getConstantValueCString());
    //dumpInstrs("sdfsdfsdfsdfsdf\n");
    if(co_str){
        //dumpInstrs("testtesttesttest\n");
        char s[100];
        sprintf(s,"    .string \"%s\"",p_constant_value.getConstantPtr()->string());
        //dumpInstrs("    .string \"%s\"\n",p_constant_value.getConstantPtr()->string());
        std::string str(s);
        la.push_back(str);
        co_str=false;
        return;
    }
    if(co_flo){
        char s[100];
        sprintf(s,"    .float %f",p_constant_value.getConstantPtr()->real());
        std::string str(s);
        la.push_back(str);
        //dumpInstrs("    .float %f\n",p_constant_value.getConstantPtr()->real());
        co_flo=false;
        return;
    }

    if(p_constant_value.getConstantPtr()->getTypePtr()->getPrimitiveType() == PType::PrimitiveTypeEnum::kIntegerType){
        dumpInstrs("    li t0, %d\n",p_constant_value.getConstantPtr()->integer());       
    }
    else if(p_constant_value.getConstantPtr()->getTypePtr()->isBool()){
        //dumpInstrs("%s\n\n",p_constant_value.getConstantPtr()->getConstantValueCString());
        if(p_constant_value.getConstantPtr()->boolean()){
            dumpInstrs("li t0, 1\n");
        }
        else{
            dumpInstrs("    li t0, 0\n");
        }
    }
    else{
        //dumpInstrs("    li t0, %s\n",p_constant_value.getConstantValueCString());    
    }
    dumpInstrs("    addi sp, sp, -4\n");
    dumpInstrs("    sw t0, 0(sp)\n");
}

void CodeGenerator::visit(FunctionNode &p_function) {
    // Reconstruct the hash table for looking up the symbol entry
    symbol_manager->reconstructHashTableFromSymbolTable(p_function.getSymbolTable());
    dep++;
    off.push_back(offset);
    offset=-12;

    dumpInstrs(".section    .text\n");
    dumpInstrs("    .align 2\n");
    dumpInstrs("    .globl %s\n",p_function.getNameCString());
    dumpInstrs("    .type %s, @function\n",p_function.getNameCString());
    dumpInstrs("%s:\n",p_function.getNameCString());
    // function prologue
    dumpInstrs("    addi sp, sp, -128\n");
    dumpInstrs("    sw ra, 124(sp)\n");
    dumpInstrs("    sw s0, 120(sp)\n");
    dumpInstrs("    addi s0, sp, 128\n");

    int ind=0;
    for (auto &parameter : p_function.getParameters()) {
        for(auto &pa: parameter->getVariables()){
            //dumpInstrs("%s\n%d\n\n",pa->getName().c_str(),find_dec_var(pa->getName()));
            if(pa->getTypePtr()->isString()){
                bool ch=true;
                for(int i=0;i<dec_var.size();i++){
                    if(dec_var[i].first==pa->getName()){
                        ch=false;
                    }
                }
                if(ch) dec_var.push_back(make_pair(pa->getName(),2));

            }
            else if(pa->getTypePtr()->isReal()){
                add_var(pa->getName());
                offset-=4;
                bool ch=true;
                if(ind<8) dumpInstrs("    sw a%d, %d(s0)\n",ind,offset+4);
                else dumpInstrs("    fsw ft0, %d(s0)\n",offset+4);
                ind++;  
                for(int i=0;i<dec_var.size();i++){
                    if(dec_var[i].first==pa->getName()){
                        ch=false;
                    }
                }
                if(ch) dec_var.push_back(make_pair(pa->getName(),1));
            }
            else{
                add_var(pa->getName());
                int sum=1;
                for (auto dimension : pa->getTypePtr()->getDimensions()){
                    sum*=dimension;
                    add_ind(pa->getName(),dimension);
                }
                for(int i=1;i<=sum;i++){
                    offset-=4;
                    if(ind<8) dumpInstrs("    sw a%d, %d(s0)\n",ind,offset+4);
                    else dumpInstrs("    sw t0, %d(s0)\n",offset+4);
                    ind++;                
                }
                //auto k=find_ind(p_variable.getName());
                //dumpInstrs("%d 1111111\n",k.size());
                //offset-=4*sum;
            }


            //dumpInstrs("%s  11111111111111\n",pa->getNameCString());
            //add_var(pa->getName());
            //offset-=4;
            //if(ind<8) dumpInstrs("    sw a%d, %d(s0)\n",ind,offset+4);
            //else dumpInstrs("    sw t0, %d(s0)\n",offset+4);
            //ind++;
        }
        //parameter->accept(p_visitor);
    }

    //dumpInstrs("11111111111111111\n");
    p_function.visitbody(*this);
    // function epilogue
    dumpInstrs("    lw ra, 124(sp)\n");
    dumpInstrs("    lw s0, 120(sp)\n");
    dumpInstrs("    addi sp, sp, 128\n");
    dumpInstrs("    jr ra\n");
    dumpInstrs("    .size %s, .-%s\n",p_function.getNameCString(),p_function.getNameCString());

    popvar();
    dep--;
    offset=off[off.size()-1];
    off.pop_back();
    //offset=-12;
    // Remove the entries in the hash table
    symbol_manager->removeSymbolsFromHashTable(p_function.getSymbolTable());
}

void CodeGenerator::visit(CompoundStatementNode &p_compound_statement) {
    
    // Reconstruct the hash table for looking up the symbol entry
    symbol_manager->reconstructHashTableFromSymbolTable(p_compound_statement.getSymbolTable());        

    p_compound_statement.visitChildNodes(*this);

    // Remove the entries in the hash table
    symbol_manager->removeSymbolsFromHashTable(p_compound_statement.getSymbolTable());
}

void CodeGenerator::visit(PrintNode &p_print) {
    //dumpInstrs("    jal ra, printReal\n");
    p_print.visitChildNodes(*this);
    //dumpInstrs("asdfedf\n");
    if(co_str){
        dumpInstrs("    jal ra, printString\n");
        co_str=false;
        return;
    }
    if(co_flo){
        dumpInstrs("    lw a0, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    jal ra, printReal\n");
        co_flo=false;
        return;
    }
    dumpInstrs("    lw a0, 0(sp)\n");
    dumpInstrs("    addi sp, sp, 4\n");
    dumpInstrs("    jal ra, printInt\n");
    
}

void CodeGenerator::visit(BinaryOperatorNode &p_bin_op) {
    in_cond=false;
    in_cond_var=false;
    p_bin_op.visitChildNodes(*this);

    switch (p_bin_op.getOp()) {
    case Operator::kPlusOp:
        if(co_flo){
            dumpInstrs("    flw ft0, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    flw ft1, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    fadd.s ft0, ft1, ft0\n");
            dumpInstrs("    addi sp, sp, -4\n");   
            dumpInstrs("    fsw ft0, 0(sp)\n");
            dumpInstrs("    flw fa0, 0(sp)\n");
            pu_flo=true;
        }
        else{
            dumpInstrs("    lw t0, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    lw t1, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    add t0, t1, t0\n");
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    sw t0, 0(sp)\n");
        }
        break;
    case Operator::kMinusOp:
        dumpInstrs("    lw t0, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    lw t1, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    sub t0, t1, t0\n");
        dumpInstrs("    addi sp, sp, -4\n");
        dumpInstrs("    sw t0, 0(sp)\n");
        break;
    case Operator::kMultiplyOp:
        dumpInstrs("    lw t0, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    lw t1, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    mul t0, t1, t0\n");
        dumpInstrs("    addi sp, sp, -4\n");
        dumpInstrs("    sw t0, 0(sp)\n");
        break;
    case Operator::kDivideOp:
        dumpInstrs("    lw t0, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    lw t1, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    div t0, t1, t0\n");
        dumpInstrs("    addi sp, sp, -4\n");
        dumpInstrs("    sw t0, 0(sp)\n");
        break;
    case Operator::kModOp:
        dumpInstrs("    lw t0, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    lw t1, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    rem t0, t1, t0\n");
        dumpInstrs("    addi sp, sp, -4\n");
        dumpInstrs("    sw t0, 0(sp)\n");
       break;
    case Operator::kAndOp:
        dumpInstrs("    lw t0, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    lw t1, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    and t0, t1, t0\n");
        dumpInstrs("    addi sp, sp, -4\n");
        dumpInstrs("    sw t0, 0(sp)\n");
        break;
    case Operator::kOrOp:
        dumpInstrs("    lw t0, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    lw t1, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    or t0, t1, t0\n");
        dumpInstrs("    addi sp, sp, -4\n");
        dumpInstrs("    sw t0, 0(sp)\n");
        break;
    case Operator::kLessOp:
        if(bo_ass){
            dumpInstrs("    lw t0, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    lw t1, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    slt t0, t1, t0\n");
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    sw t0, 0(sp)\n");
        }
        else{
            if(p_bin_op.tr>0&&p_bin_op.fl>0){
                dumpInstrs("    lw t0, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    lw t1, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    blt t1, t0, L%d\n",p_bin_op.tr);
                dumpInstrs("    j L%d\n",p_bin_op.fl);
            }
            else{
                dumpInstrs("    lw t0, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    lw t1, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    slt t0, t1, t0\n");
                dumpInstrs("    addi sp, sp, -4\n");
                dumpInstrs("    sw t0, 0(sp)\n");
            }
        }
        break;
    case Operator::kLessOrEqualOp:
        if(bo_ass){
            dumpInstrs("    lw t0, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    lw t1, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    slt t0, t0, t1\n");
            dumpInstrs("    li t1, 1\n");
            dumpInstrs("    xor t0, t0, t1\n");
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    sw t0, 0(sp)\n");
        }
        else{
            if(p_bin_op.tr>0&&p_bin_op.fl>0){
                dumpInstrs("    lw t0, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    lw t1, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    ble t1, t0, L%d\n",p_bin_op.tr);
                dumpInstrs("    j L%d\n",p_bin_op.fl);
            }
            else{
                dumpInstrs("    lw t0, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    lw t1, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    slt t0, t0, t1\n");
                dumpInstrs("    li t1, 1\n");
                dumpInstrs("    xor t0, t0, t1\n");
                dumpInstrs("    addi sp, sp, -4\n");
                dumpInstrs("    sw t0, 0(sp)\n");
            }
        }
        break;
    case Operator::kEqualOp:
        if(bo_ass){
            dumpInstrs("    lw t0, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    lw t1, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    seq t0, t1, t0\n");
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    sw t0, 0(sp)\n");
        }
        else{
            if(p_bin_op.tr>0&&p_bin_op.fl>0){
                dumpInstrs("    lw t0, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    lw t1, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    beq t1, t0, L%d\n",p_bin_op.tr);
                dumpInstrs("    j L%d\n",p_bin_op.fl);
            }
            else{
                dumpInstrs("    lw t0, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    lw t1, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    seq t0, t1, t0\n");
                dumpInstrs("    addi sp, sp, -4\n");
                dumpInstrs("    sw t0, 0(sp)\n");                
            }
        }
        break;
    case Operator::kGreaterOp:
        if(bo_ass){
            dumpInstrs("    lw t0, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    lw t1, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    sgt t0, t1, t0\n");
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    sw t0, 0(sp)\n");
        }
        else{
            if(p_bin_op.tr>0&&p_bin_op.fl>0){
                dumpInstrs("    lw t0, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    lw t1, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    bgt t1, t0, L%d\n",p_bin_op.tr);
                dumpInstrs("    j L%d\n",p_bin_op.fl);
            }
            else{                
                dumpInstrs("    lw t0, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    lw t1, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    sgt t0, t1, t0\n");
                dumpInstrs("    addi sp, sp, -4\n");
                dumpInstrs("    sw t0, 0(sp)\n");
            }
        }
        break;
    case Operator::kGreaterOrEqualOp:
        if(bo_ass){
            dumpInstrs("    lw t0, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    lw t1, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    sge t0, t1, t0\n");
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    sw t0, 0(sp)\n");
        }
        else{
            if(p_bin_op.tr>0&&p_bin_op.fl>0){
                dumpInstrs("    lw t0, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    lw t1, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    bge t1, t0, L%d\n",p_bin_op.tr);
                dumpInstrs("    j L%d\n",p_bin_op.fl);
            }
            else{
                dumpInstrs("    lw t0, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    lw t1, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    sge t0, t1, t0\n");
                dumpInstrs("    addi sp, sp, -4\n");
                dumpInstrs("    sw t0, 0(sp)\n");
            }
        }
        break;
    case Operator::kNotEqualOp:
        if(bo_ass){
            dumpInstrs("    lw t0, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    lw t1, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    sne t0, t1, t0\n");
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    sw t0, 0(sp)\n");
        }
        else{
            if(p_bin_op.tr>0&&p_bin_op.fl>0){
                dumpInstrs("    lw t0, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    lw t1, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    bne t1, t0, L%d\n",p_bin_op.tr);
                dumpInstrs("    j L%d\n",p_bin_op.fl);
            }
            else{
                dumpInstrs("    lw t0, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    lw t1, 0(sp)\n");
                dumpInstrs("    addi sp, sp, 4\n");
                dumpInstrs("    sne t0, t1, t0\n");
                dumpInstrs("    addi sp, sp, -4\n");
                dumpInstrs("    sw t0, 0(sp)\n");
            }
        }
        break;
    default:
        break;
    }
}

void CodeGenerator::visit(UnaryOperatorNode &p_un_op) {
    p_un_op.visitChildNodes(*this);

    switch (p_un_op.getOp()) {
    case Operator::kNegOp:
        dumpInstrs("    li t0, -1\n");    
        dumpInstrs("    addi sp, sp, -4\n");
        dumpInstrs("    sw t0, 0(sp)\n");
        dumpInstrs("    lw t0, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    lw t1, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    mul t0, t1, t0\n");
        dumpInstrs("    addi sp, sp, -4\n");
        dumpInstrs("    sw t0, 0(sp)\n");
        break;
    case Operator::kNotOp:
        dumpInstrs("    lw t0, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    li t1, 0\n");
        dumpInstrs("    beq t0, t1, L%d\n",p_un_op.tr);
        dumpInstrs("    j L%d\n",p_un_op.fl);
        break;
    default:
        break;
    }
}

void CodeGenerator::visit(FunctionInvocationNode &p_func_invocation) {
    //dumpInstrs("    1111111111111111111111111111\n");
    in_cond_var=false;
    arg=0;
    p_func_invocation.visitChildNodes(*this);

    auto &arguments = p_func_invocation.getArguments();
    //dumpInstrs("%d\n\n",arguments.size());
    //dumpInstrs("%d\n",arg);
    for(int i=arguments.size()-1+arg;i>=0;i--){
        if(i<8){
            dumpInstrs("    lw a%d, 0(sp)\n",i);
            dumpInstrs("    addi sp, sp, 4\n");
        }
        else{
            dumpInstrs("    lw t0, 0(sp)\n");
            dumpInstrs("    sw t0, -12(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
        }
    }

    dumpInstrs("    jal ra, %s\n",p_func_invocation.getNameCString());
    dumpInstrs("    mv t0, a0\n");
    dumpInstrs("    addi sp, sp, -4\n");
    dumpInstrs("    sw t0, 0(sp)\n");
    
    if(in_cond){
        dumpInstrs("    lw t1, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");
        dumpInstrs("    li t0, 0\n");

        dumpInstrs("    bne t1, t0, L%d\n",p_func_invocation.tr);
        dumpInstrs("    j L%d\n",p_func_invocation.fl);
    }
    
}

void CodeGenerator::visit(VariableReferenceNode &p_variable_ref) {
    //dumpInstrs("1212323kjlsfdj\n");
    p_variable_ref.visitChildNodes(*this);
    
    auto *entry = symbol_manager->lookup(p_variable_ref.getName());
    if(find_dec_var(p_variable_ref.getName())==2){
        //dumpInstrs("123123\n");
        dumpInstrs("    lui t0, %%hi(%s)\n",p_variable_ref.getName().c_str());
        dumpInstrs("    addi a0, t0, %%lo(%s)\n",p_variable_ref.getName().c_str());
        co_str=true;
    }
    else if(find_dec_var(p_variable_ref.getName())==1){
        if(pu_flo){
            dumpInstrs("    flw ft0, %d(s0)\n",find_var(p_variable_ref.getName()));
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    fsw ft0, 0(sp)\n");
            pu_flo=false;
        }
        else{
            dumpInstrs("    lui t0, %%hi(%s)\n",p_variable_ref.getName().c_str());
            dumpInstrs("    flw fa0, %%lo(%s)(t0)\n",p_variable_ref.getName().c_str());
            dumpInstrs("    flw ft0, %%lo(%s)(t0)\n",p_variable_ref.getName().c_str());
            dumpInstrs("    fsw ft0, %d(s0)\n",find_var(p_variable_ref.getName()));
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    fsw ft0, 0(sp)\n");
            dumpInstrs("    flw fa0, %d(s0)\n",find_var(p_variable_ref.getName()));
        }
        co_flo=true;
    }
    else if(find_var(p_variable_ref.getName())!=0){
        if(re==false){
            int index_max[20];
            int j=0;
            for(auto index:find_ind(p_variable_ref.getName())){
                index_max[j]=index;
                j++;
            }
            for(int i=p_variable_ref.getIndices().size()-1;i>=0;i--){
                    if(i==0){
                        dumpInstrs("    lw t0, 0(sp)\n");
                        dumpInstrs("    addi sp, sp, 4\n");
                        dumpInstrs("    li t1, -4\n");
                        dumpInstrs("    mul t0, t0, t1\n");
                        dumpInstrs("    addi t0, t0, %d\n",find_var(p_variable_ref.getName()));
                        dumpInstrs("    add t0, t0, s0\n");
                        dumpInstrs("    lw t0, 0(t0)\n");
                        dumpInstrs("    addi sp, sp, -4\n");
                        dumpInstrs("    sw t0, 0(sp)\n");
                    }
                    else{
                        dumpInstrs("    lw t0, 0(sp)\n");
                        dumpInstrs("    addi sp, sp, 4\n");
                        dumpInstrs("    li t1, %d\n",index_max[i-1]);
                        dumpInstrs("    mul t0, t0, t1\n");
                        dumpInstrs("    lw t1, 0(sp)\n");
                        dumpInstrs("    addi sp, sp, 4\n");
                        dumpInstrs("    add t0, t1, t0\n");
                        dumpInstrs("    addi sp, sp, -4\n");
                        dumpInstrs("    sw t0, 0(sp)\n");
                        
                    }
            }
            //for (auto dimension : p_variable.getTypePtr()->getDimensions()){
            //    dumpInstrs("%d  123123123\n",dimension);
            //}
            if(find_ind(p_variable_ref.getName()).size()!=0&&p_variable_ref.getIndices().size()==0){
                int su=1;
                int x=find_var(p_variable_ref.getName());
                for(auto index:find_ind(p_variable_ref.getName())){
                    su*=index;
                }
                for(int j=0;j<su;j++){
                    dumpInstrs("    lw t0, %d(s0)\n",x+j*(-4));
                    dumpInstrs("    addi sp, sp, -4\n");
                    dumpInstrs("    sw t0, 0(sp)\n");
                    arg++;
                }
                arg--;
            }
            else if(p_variable_ref.getIndices().size()==0){
                if(in_cond_var){
                    dumpInstrs("    lw t0, %d(s0)\n",find_var(p_variable_ref.getName()));
                    dumpInstrs("    li t1, 0\n");
                    dumpInstrs("    bne t0, t1, L%d\n",p_variable_ref.tr);
                    dumpInstrs("    j L%d\n",p_variable_ref.fl);
                }
                else{
                    dumpInstrs("    lw t0, %d(s0)\n",find_var(p_variable_ref.getName()));
                    dumpInstrs("    addi sp, sp, -4\n");
                    dumpInstrs("    sw t0, 0(sp)\n");
                }
            }
        }
        else{
            int index_max[20];
            int j=0;
            for(auto index:find_ind(p_variable_ref.getName())){
                index_max[j]=index;
                j++;
            }
            for(int i=p_variable_ref.getIndices().size()-1;i>=0;i--){
                    if(i==0){
                        dumpInstrs("    lw t0, 0(sp)\n");
                        dumpInstrs("    addi sp, sp, 4\n");
                        dumpInstrs("    li t1, -4\n");
                        dumpInstrs("    mul t0, t0, t1\n");
                        dumpInstrs("    addi t0, t0, %d\n",find_var(p_variable_ref.getName()));
                        dumpInstrs("    add t0, t0, s0\n");
                        dumpInstrs("    addi sp, sp, -4\n");
                        dumpInstrs("    sw t0, 0(sp)\n");
                    }
                    else{
                        dumpInstrs("    lw t0, 0(sp)\n");
                        dumpInstrs("    addi sp, sp, 4\n");
                        dumpInstrs("    li t1, %d\n",index_max[i-1]);
                        dumpInstrs("    mul t0, t0, t1\n");
                        dumpInstrs("    lw t1, 0(sp)\n");
                        dumpInstrs("    addi sp, sp, 4\n");
                        dumpInstrs("    add t0, t1, t0\n");
                        dumpInstrs("    addi sp, sp, -4\n");
                        dumpInstrs("    sw t0, 0(sp)\n");
                        
                    }
            }
            if(p_variable_ref.getIndices().size()==0){
            dumpInstrs("    addi t0, s0, %d\n",find_var(p_variable_ref.getName()));
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    sw t0, 0(sp)\n");
            }
            re=false;
        }
    }
    else if(entry!=NULL&&entry->getKind() == SymbolEntry::KindEnum::kVariableKind && entry->getLevel()==0 ){
        if(re==false){
            dumpInstrs("    la t0, %s\n",p_variable_ref.getName().c_str());
            dumpInstrs("    lw t1, 0(t0)\n");
            dumpInstrs("    mv t0, t1\n");
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    sw t0, 0(sp)\n");
        }
        else{
            dumpInstrs("    la t0, %s\n",p_variable_ref.getName().c_str());
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    sw t0, 0(sp)\n");
            re=false;
        }
    }
    else if(entry!=NULL&&entry->getKind() == SymbolEntry::KindEnum::kConstantKind && entry->getLevel()==0 ){
        if(re==false){
            dumpInstrs("    la t0, %s\n",p_variable_ref.getName().c_str());
            dumpInstrs("    lw t1, 0(t0)\n");
            dumpInstrs("    mv t0, t1\n");
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    sw t0, 0(sp)\n");
        }
        else{
            dumpInstrs("    la t0, %s\n",p_variable_ref.getName().c_str());
            dumpInstrs("    addi sp, sp, -4\n");
            dumpInstrs("    sw t0, 0(sp)\n");
            re=false;
        }
    }


}

void CodeGenerator::visit(AssignmentNode &p_assignment) {

    auto *entry = symbol_manager->lookup(p_assignment.getLvalue()->getName());
    //dumpInstrs("asdfadsfadsfasdfasdf\n");
    //dumpInstrs("%s\n",p_assignment.getLvalue()->getName().c_str());
    if(find_dec_var(p_assignment.getLvalue()->getName())==1){

        char a[100];
        sprintf(a,"    .section	.rodata");
        std::string str(a);
        la.push_back(str);
        char b[100];
        sprintf(b,"    .align	2");
        std::string str1(b);
        la.push_back(str1);
        char c[100];
        sprintf(c,"%s:",p_assignment.getLvalue()->getName().c_str());
        std::string str2(c);
        la.push_back(str2);

        co_flo=true;
        p_assignment.visitexpr(*this);
        if(pu_flo){
            //dumpInstrs("123123123\n");
            dumpInstrs("    flw ft0, 0(sp)\n");
            dumpInstrs("    addi sp, sp, 4\n");
            dumpInstrs("    fsw ft0, %d(s0)\n",find_var(p_assignment.getLvalue()->getName()));
        }
        return;
    }
    else if(find_dec_var(p_assignment.getLvalue()->getName())==2){
        
        char a[100];
        sprintf(a,"    .section	.rodata");
        std::string str(a);
        la.push_back(str);
        char b[100];
        sprintf(b,"    .align	2");
        std::string str1(b);
        la.push_back(str1);
        char c[100];
        sprintf(c,"%s:",p_assignment.getLvalue()->getName().c_str());
        std::string str2(c);
        la.push_back(str2);
        
        //dumpInstrs("    .section	.rodata\n");
        //dumpInstrs("    .align	2\n");
        //dumpInstrs("%s:\n",p_assignment.getLvalue()->getName().c_str());
        co_str=true;
        p_assignment.visitexpr(*this);
        return;
    }
    else if(find_dec_var(p_assignment.getLvalue()->getName())==3){
        bo_ass=true;
        p_assignment.visitexpr(*this);
        //dumpInstrs("abcdefg\n");
        dumpInstrs("    lw t0, 0(sp)\n");
        dumpInstrs("    addi sp, sp, 4\n");

        dumpInstrs("    addi t1, s0, %d\n",find_var(p_assignment.getLvalue()->getName()));
        dumpInstrs("    sw t0, 0(t1)\n");
        bo_ass=false;
        return;
    }

    if(find_var(p_assignment.getLvalue()->getName())!=0){
            re=true;
            p_assignment.visitlval(*this);

    }
    else if(entry!=NULL&&entry->getKind() == SymbolEntry::KindEnum::kVariableKind && entry->getLevel()==0 ){
        dumpInstrs("    la t0, %s\n",p_assignment.getLvalue()->getName().c_str());
        dumpInstrs("    addi sp, sp, -4\n");
        dumpInstrs("    sw t0, 0(sp)\n");
    }
    else if(entry!=NULL&&entry->getKind() == SymbolEntry::KindEnum::kConstantKind && entry->getLevel()==0 ){
        dumpInstrs("    la t0, %s\n",p_assignment.getLvalue()->getName().c_str());
        dumpInstrs("    addi sp, sp, -4\n");
        dumpInstrs("    sw t0, 0(sp)\n");
    }
    //dumpInstrs("asdfadsfadsfasdfasdf\n");

    p_assignment.visitexpr(*this);
    //dumpInstrs("   *************\n");
    dumpInstrs("    lw t0, 0(sp)\n");
    dumpInstrs("    addi sp, sp, 4\n");
    dumpInstrs("    lw t1, 0(sp)\n");
    dumpInstrs("    addi sp, sp, 4\n");
    dumpInstrs("    sw t0, 0(t1)\n");
    //dumpInstrs("   *************\n");

}

void CodeGenerator::visit(ReadNode &p_read) {
    re=true;
    p_read.visitChildNodes(*this);
    dumpInstrs("    jal ra, readInt\n");
    dumpInstrs("    lw t0, 0(sp)\n");
    dumpInstrs("    addi sp, sp, 4\n");
    dumpInstrs("    sw a0, 0(t0)\n");
}

void CodeGenerator::visit(IfNode &p_if) {
    //dumpInstrs("    1111111111111111111111111111\n");
    int c1,c2,c3;
    c1=le;
    le++;
    c2=le;
    le++;
    c3=le;
    le++;
    p_if.getCond()->tr=c1;
    p_if.getCond()->fl=c2;
    in_cond=true;
    in_cond_var=true;
    p_if.visitcond(*this);
    in_cond=false;
    in_cond_var=false;
    dumpInstrs("L%d:\n",c1);
    p_if.visitbody(*this);
    if(p_if.elsebody(*this)){
        dumpInstrs("    j L%d\n",c3);
    }
    dumpInstrs("L%d:\n",c2);
    if(p_if.elsebody(*this)){
        p_if.visitelse(*this);
        dumpInstrs("L%d:\n",c3);
    }
    
}

void CodeGenerator::visit(WhileNode &p_while) {
    int c1,c2,c3;
    c1=le;
    le++;
    c2=le;
    le++;
    c3=le;
    le++;
    p_while.getCond()->tr=c2;
    p_while.getCond()->fl=c3;
    dumpInstrs("L%d:\n",c1);
    p_while.visitcond(*this);
    dumpInstrs("L%d:\n",c2);
    p_while.visitbody(*this);
    dumpInstrs("    j L%d\n",c1);
    dumpInstrs("L%d:\n",c3);

}

void CodeGenerator::visit(ForNode &p_for) {
    // Reconstruct the hash table for looking up the symbol entry
    symbol_manager->reconstructHashTableFromSymbolTable(p_for.getSymbolTable());
    dep++;
    off.push_back(offset);
    //offset=-12;
    //dumpInstrs("1111111111111111111111\n");
    p_for.visit_dec_and_assign(*this);
    //dumpInstrs("1111111111111111111111\n");

    int c1,c2,c3;
    c1=le;
    le++;
    c2=le;
    le++;
    c3=le;
    le++;
    dumpInstrs("L%d:\n",c1);
    dumpInstrs("    lw t0, %d(s0)\n",find_var(p_for.getdecl()->getVariables()[0]->getName()));
    dumpInstrs("    addi sp, sp, -4\n");
    dumpInstrs("    sw t0, 0(sp)\n");
    p_for.visit_constantvalue(*this);
    dumpInstrs("    lw t0, 0(sp)\n");
    dumpInstrs("    addi sp, sp, 4\n");
    dumpInstrs("    lw t1, 0(sp)\n");
    dumpInstrs("    addi sp, sp, 4\n");
    dumpInstrs("    bge t1, t0, L%d\n",c3);
    dumpInstrs("L%d:\n",c2);
    p_for.visit_body(*this);
    //dumpInstrs("1111111111111111111111\n");
    dumpInstrs("    addi t0, s0, %d\n",find_var(p_for.getdecl()->getVariables()[0]->getName()));
    dumpInstrs("    addi sp, sp, -4\n");
    dumpInstrs("    sw t0, 0(sp)\n");
    dumpInstrs("    lw t0, %d(s0)\n",find_var(p_for.getdecl()->getVariables()[0]->getName()));
    dumpInstrs("    addi sp, sp, -4\n");
    dumpInstrs("    sw t0, 0(sp)\n");
    dumpInstrs("    li t0, 1\n");
    dumpInstrs("    addi sp, sp, -4\n");
    dumpInstrs("    sw t0, 0(sp)\n");
    dumpInstrs("    lw t0, 0(sp) \n");
    dumpInstrs("    addi sp, sp, 4\n");
    dumpInstrs("    lw t1, 0(sp)\n");
    dumpInstrs("    addi sp, sp, 4\n");
    dumpInstrs("    add t0, t1, t0 \n");
    dumpInstrs("    addi sp, sp, -4\n");
    dumpInstrs("    sw t0, 0(sp)\n");
    dumpInstrs("    lw t0, 0(sp)\n");
    dumpInstrs("    addi sp, sp, 4\n");
    dumpInstrs("    lw t1, 0(sp)\n");
    dumpInstrs("    addi sp, sp, 4\n");
    dumpInstrs("    sw t0, 0(t1)\n");
    //dumpInstrs("1111111111111111111111\n");
    dumpInstrs("    j L%d\n",c1);
    dumpInstrs("L%d:\n",c3);


    popvar();
    dep--;
    offset=off[off.size()-1];
    off.pop_back();
    //offset=-12;
    // Remove the entries in the hash table
    symbol_manager->removeSymbolsFromHashTable(p_for.getSymbolTable());
}

void CodeGenerator::visit(ReturnNode &p_return) {

    p_return.visitChildNodes(*this);
    dumpInstrs("    lw t0, 0(sp)\n");
    dumpInstrs("    addi sp, sp, 4\n");
    dumpInstrs("    mv a0, t0\n");
}