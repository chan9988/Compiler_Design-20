#include "sema/SemanticAnalyzer.hpp"
#include "visitor/AstNodeInclude.hpp"

#include <cstring>

void SemanticAnalyzer::visit(ProgramNode &p_program) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */

	fun.push_back(p_program.getNameCString());
	SymbolTable *new_scope=new SymbolTable;
	ma.pushScope(new_scope);
	SymbolEntry n;
	n.name=p_program.getNameCString();
	n.kind="program";
	n.type=p_program.getTypeCString();
	n.attribute=NULL;
	ma.pushentry(n);
	p_program.visitChildNodes(*this);

	if(turndump) ma.print_top();
	ma.free_top();
	ma.popScope();
	fun.pop_back();
}

void SemanticAnalyzer::visit(DeclNode &p_decl) {
    p_decl.visitChildNodes(*this);
}

void SemanticAnalyzer::visit(VariableNode &p_variable) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
	//std::cout << p_variable.getLocation().line << " " << p_variable.getLocation().col << std::endl;
	//int col=p_variable.getLocation().col;
	//while(col--){
	//	if(col==0) printf("^\n");
	//	else printf(" ");
	//}

	if(ma.check_decl(p_variable.getNameCString())){
		has_error=true;	
		error_handle e;
		e.line=p_variable.getLocation().line;
		e.col=p_variable.getLocation().col;
		sprintf(e.str,"<Error> Found in line %d, column %d: symbol '%s' is redeclared",e.line,e.col,p_variable.getNameCString());
		er.push_back(e);
		//p_variable.use=false;
	}
	else{
		SymbolEntry n;
		n.name=p_variable.getNameCString();
		write_to_var=true;
		if(need_var==true){
			//std::cout << 123 << std::endl;
			n.kind="loop_var";
			if(p_variable.check_ptype()){
					has_error=true;	
					error_handle e;
					e.line=p_variable.getLocation().line;
					e.col=p_variable.getLocation().col;
					sprintf(e.str,"<Error> Found in line %d, column %d: '%s' declared as an array with an index that is not greater than 0",e.line,e.col,p_variable.getNameCString());
					er.push_back(e);
					n.valid=false;
			}
			n.n_ptype=p_variable.ptype_num();
			n.type=p_variable.getTypeCString();
			n.attribute=NULL;
			ma.pushentry(n);
		}
		else if(need_par==true){
			n.kind="parameter";
			if(p_variable.check_ptype()){
					has_error=true;	
					error_handle e;
					e.line=p_variable.getLocation().line;
					e.col=p_variable.getLocation().col;
					sprintf(e.str,"<Error> Found in line %d, column %d: '%s' declared as an array with an index that is not greater than 0",e.line,e.col,p_variable.getNameCString());
					er.push_back(e);
					n.valid=false;
			}
			n.n_ptype=p_variable.ptype_num();
			n.type=p_variable.getTypeCString();
			n.attribute=NULL;
			ma.pushentry(n);
		}
		else{
			n.kind="variable";
			if(p_variable.check_ptype()){
					has_error=true;	
					error_handle e;
					e.line=p_variable.getLocation().line;
					e.col=p_variable.getLocation().col;
					sprintf(e.str,"<Error> Found in line %d, column %d: '%s' declared as an array with an index that is not greater than 0",e.line,e.col,p_variable.getNameCString());
					er.push_back(e);
					n.valid=false;
			}
			n.n_ptype=p_variable.ptype_num();
			n.type=p_variable.getTypeCString();
			n.attribute=NULL;
			ma.pushentry(n);
			p_variable.visitChildNodes(*this);
		}
		write_to_var=false;
	}
}

void SemanticAnalyzer::visit(ConstantValueNode &p_constant_value) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
	//std::cout << p_constant_value.getConstantValueCString() << std::endl;
	if(need_var==false&&write_to_var==true){
		ma.tables[ma.tables.size()-1]->entries[ma.tables[ma.tables.size()-1]->entries.size()-1].kind="constant";
		ma.tables[ma.tables.size()-1]->entries[ma.tables[ma.tables.size()-1]->entries.size()-1].attribute=p_constant_value.getConstantValueCString();
	}
	//strcpy(ma.tables.top()->entries[ma.tables.top()->entries.size()-1].attribute,"123456");
	
	p_constant_value.type=p_constant_value.getTypePtr();
	if(need_for_init){
		strcpy(for_init,p_constant_value.getConstantValueCString());
		need_for_init=false;
	}
	//if( p_constant_value.getTypePtr()->getPrimitiveType() == PType::PrimitiveTypeEnum::kIntegerType) printf("Integer\n");
	//else printf("Not Integer\n");
	
}

void SemanticAnalyzer::visit(FunctionNode &p_function) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
	fun.push_back(p_function.getNameCString());
	if(ma.check_decl(p_function.getNameCString())){
		has_error=true;	
		error_handle e;
		e.line=p_function.getLocation().line;
		e.col=p_function.getLocation().col;
		sprintf(e.str,"<Error> Found in line %d, column %d: symbol '%s' is redeclared",e.line,e.col,p_function.getNameCString());
		er.push_back(e);
	}
	else{
		SymbolEntry n;
		n.name=p_function.getNameCString();
		n.kind="function";
		n.type=p_function.getTypeCString();
		n.attribute=p_function.getinputtype();
		ma.pushentry(n);
	}
	SymbolTable *new_scope=new SymbolTable;
	ma.pushScope(new_scope);
	need_par=true;
	if(p_function.isDefined()){
		need_cs=true;
	};
	p_function.visitChildNodes(*this);

	if(turndump) ma.print_top();
	ma.free_top();
	ma.popScope();
	fun.pop_back();
}

void SemanticAnalyzer::visit(CompoundStatementNode &p_compound_statement) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
	if(need_cs==true){
		need_par=false;
		need_cs=false;
		need_var=false;
		p_compound_statement.visitChildNodes(*this);
	}
	else{	
		need_par=false;
		need_var=false;
		SymbolTable *new_scope=new SymbolTable;
		ma.pushScope(new_scope);
		p_compound_statement.visitChildNodes(*this);

		if(turndump) ma.print_top();
		ma.free_top();
		ma.popScope();
	}	
}

void SemanticAnalyzer::visit(PrintNode &p_print) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */

	p_print.visitChildNodes(*this);
	if(p_print.target!=NULL&&(p_print.target->dim!=0||strcmp(p_print.target->t,"void")==0)){
		has_error=true;	
		error_handle e;
		e.line=p_print.target->getLocation().line;
		e.col=p_print.target->getLocation().col;
		sprintf(e.str,"<Error> Found in line %d, column %d: expression of print statement must be scalar type",e.line,e.col);
		er.push_back(e);	
	}

}

void SemanticAnalyzer::visit(BinaryOperatorNode &p_bin_op) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
	p_bin_op.visitChildNodes(*this);
	//printf("%s\n",p_bin_op.getOpCString());
	//if(p_variable_ref.indices[i]->type->getPrimitiveType()!=PType::PrimitiveTypeEnum::kIntegerType)

	char ltype[50],rtype[50];
	char lm[50],rm[50];
	bool err=false;
	if(p_bin_op.left->type!=NULL&&p_bin_op.right->type!=NULL){
		if(p_bin_op.left->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kIntegerType) strcpy(ltype,"integer");
		else if(p_bin_op.left->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kRealType) strcpy(ltype,"real");
		else if(p_bin_op.left->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kStringType) strcpy(ltype,"string");
		else if(p_bin_op.left->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kBoolType) strcpy(ltype,"boolean");
		else if(p_bin_op.left->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kVoidType) strcpy(ltype,"void");
		if(p_bin_op.right->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kIntegerType) strcpy(rtype,"integer");
		else if(p_bin_op.right->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kRealType) strcpy(rtype,"real");
		else if(p_bin_op.right->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kStringType) strcpy(rtype,"string");
		else if(p_bin_op.right->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kBoolType) strcpy(rtype,"boolean");
		else if(p_bin_op.right->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kVoidType) strcpy(rtype,"void");	

		strcpy(lm,ltype);
		strcpy(rm,rtype);
		for(int i=0;i<p_bin_op.left->dim;i++){
			if(i==0) strcat(lm," ");
			strcat(lm,"[1]");
		}
		for(int i=0;i<p_bin_op.right->dim;i++){
			if(i==0) strcat(rm," ");
			strcat(rm,"[1]");
		}
	}


	if(strcmp(p_bin_op.getOpCString(),"+")==0||strcmp(p_bin_op.getOpCString(),"-")==0||strcmp(p_bin_op.getOpCString(),"*")==0||strcmp(p_bin_op.getOpCString(),"/")==0){
		if(p_bin_op.left->type!=NULL&&p_bin_op.right->type!=NULL){
			if((strcmp(ltype,"integer")==0||strcmp(ltype,"real")==0)&&(strcmp(rtype,"integer")==0||strcmp(rtype,"real")==0)){
				if((p_bin_op.left->dim==p_bin_op.right->dim&&strcmp(p_bin_op.left->t,p_bin_op.right->t)==0)||(p_bin_op.left->dim==0&&p_bin_op.right->dim==0)){
					if(strcmp(ltype,"integer")==0&&strcmp(rtype,"integer")==0){
						p_bin_op.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kIntegerType);
						//int d=ma.find_var_ptype_num(p_bin_op.getNameCString())-p_bin_op.indices.size();
						p_bin_op.dim=0;						
					}
					else{
						p_bin_op.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kRealType);
						//int d=ma.find_var_ptype_num(p_bin_op.getNameCString())-p_bin_op.indices.size();
						p_bin_op.dim=0;
					}
				}
				else  err=true;
			}
			else if(strcmp(ltype,"string")==0&&strcmp(rtype,"string")==0&&strcmp(p_bin_op.getOpCString(),"+")==0){
				p_bin_op.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kStringType);
				//int d=ma.find_var_ptype_num(p_bin_op.getNameCString())-p_bin_op.indices.size();
				p_bin_op.dim=0;
			}
			else err=true;
		}
	}
	else if(strcmp(p_bin_op.getOpCString(),"mod")==0){
		if(p_bin_op.left->type!=NULL&&p_bin_op.right->type!=NULL){
			if(strcmp(ltype,"integer")==0&&strcmp(rtype,"integer")==0){
				p_bin_op.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kIntegerType);
				p_bin_op.dim=0;
			}
			else err=true;
		}

	}
	else if(strcmp(p_bin_op.getOpCString(),"and")==0||strcmp(p_bin_op.getOpCString(),"or")==0){
		if(p_bin_op.left->type!=NULL&&p_bin_op.right->type!=NULL){
			if(strcmp(ltype,"boolean")==0&&strcmp(rtype,"boolean")==0){
				if(p_bin_op.left->dim!=0||p_bin_op.right->dim!=0) err=true;
				else{
					p_bin_op.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kBoolType);
					p_bin_op.dim=0;
				}
			}
			else err=true;
		}
	}
	else if(strcmp(p_bin_op.getOpCString(),"<")==0||strcmp(p_bin_op.getOpCString(),"<=")==0||strcmp(p_bin_op.getOpCString(),"=")==0||strcmp(p_bin_op.getOpCString(),">=")==0||strcmp(p_bin_op.getOpCString(),">")==0||strcmp(p_bin_op.getOpCString(),"<>")==0){

		if(p_bin_op.left->type!=NULL&&p_bin_op.right->type!=NULL){
			if((strcmp(ltype,"integer")==0||strcmp(ltype,"real")==0)&&(strcmp(rtype,"integer")==0||strcmp(rtype,"real")==0)){
				if(p_bin_op.left->dim==0&&p_bin_op.right->dim==0){
					p_bin_op.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kBoolType);
					p_bin_op.dim=0;
				}
				else if(p_bin_op.left->dim==p_bin_op.right->dim&&strcmp(p_bin_op.left->t,p_bin_op.right->t)==0){
					p_bin_op.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kBoolType);
					p_bin_op.dim=0;
				}
				else err=true;
			}
			else err=true;
		}
	}
	

	if(err){
		has_error=true;	
		error_handle e;
		e.line=p_bin_op.getLocation().line;
		e.col=p_bin_op.getLocation().col;
		sprintf(e.str,"<Error> Found in line %d, column %d: invalid operands to binary operator '%s' ('%s' and '%s')",e.line,e.col,p_bin_op.getOpCString(),lm,rm);
		er.push_back(e);
	}
}

void SemanticAnalyzer::visit(UnaryOperatorNode &p_un_op) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
	p_un_op.visitChildNodes(*this);

	bool err=false;
	char ltype[50],lm[50];

	if(p_un_op.operand->type!=NULL){
		if(p_un_op.operand->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kIntegerType) strcpy(ltype,"integer");
		else if(p_un_op.operand->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kRealType) strcpy(ltype,"real");
		else if(p_un_op.operand->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kStringType) strcpy(ltype,"string");
		else if(p_un_op.operand->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kBoolType) strcpy(ltype,"boolean");
		else if(p_un_op.operand->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kVoidType) strcpy(ltype,"void");
		strcpy(lm,p_un_op.operand->t);
	}


	//printf("%s\n",p_un_op.getOpCString());
	if(strcmp(p_un_op.getOpCString(),"neg")==0){
		if(p_un_op.operand->type!=NULL){
			if(p_un_op.operand->dim>0) err=true;
			else if(strcmp(ltype,"integer")==0){
				p_un_op.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kIntegerType);
				p_un_op.dim=0;				
			}
			else if(strcmp(ltype,"real")==0){
				p_un_op.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kRealType);
				p_un_op.dim=0;
			}
			else err=true;
		}
	}
	else if(strcmp(p_un_op.getOpCString(),"not")==0){
		if(p_un_op.operand->type!=NULL){
			if(p_un_op.operand->dim>0) err=true;
			else if(strcmp(ltype,"boolean")==0){
				p_un_op.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kBoolType);
				p_un_op.dim=0;
			}
			else err=true;
		}
	}
	//printf("123\n");	
	if(err){
		has_error=true;	
		error_handle e;
		e.line=p_un_op.getLocation().line;
		e.col=p_un_op.getLocation().col;
		sprintf(e.str,"<Error> Found in line %d, column %d: invalid operand to unary operator '%s' ('%s')",e.line,e.col,p_un_op.getOpCString(),lm);
		er.push_back(e);
	}

}

void SemanticAnalyzer::visit(FunctionInvocationNode &p_func_invocation) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */

	p_func_invocation.visitChildNodes(*this);

	if(ma.find_fun_return_type(p_func_invocation.getNameCString())!=NULL){
		char s[50][50];
		int max=0;
		const char *c=ma.find_fun_attr(p_func_invocation.getNameCString());
		char cm[50];
		int i=0;
		int j=0;
		while(c[i]!='\0'){
			s[max][j]=c[i];
			i++;
			j++;
			if(c[i]==','||c[i]=='\0'){
				s[max][j]='\0';
				j=0;
				max++;
				if(c[i]==',') i+=2;
			}
		}
		//printf("%d\n",max);
		//for(i=0;i<max;i++) printf("%s\n",s[i]);

		bool err=true;		

		if(p_func_invocation.arguments.size()!=max){
			has_error=true;	
			error_handle e;
			e.line=p_func_invocation.getLocation().line;
			e.col=p_func_invocation.getLocation().col;
			sprintf(e.str,"<Error> Found in line %d, column %d: too few/much arguments provided for function '%s'",e.line,e.col,p_func_invocation.getNameCString());
			er.push_back(e);
			err=false;
		}
		else{
			for(i=0;i<p_func_invocation.arguments.size();i++){
				if(p_func_invocation.arguments[i]->type!=NULL){
					if(p_func_invocation.arguments[i]->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kIntegerType) strcpy(cm,"integer");
					else if(p_func_invocation.arguments[i]->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kRealType) strcpy(cm,"real");
					else if(p_func_invocation.arguments[i]->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kStringType) strcpy(cm,"string");
					else if(p_func_invocation.arguments[i]->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kBoolType) strcpy(cm,"boolean");
					else if(p_func_invocation.arguments[i]->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kVoidType) strcpy(cm,"void");

					if(strcmp(cm,s[i])!=0){
						if(p_func_invocation.arguments[i]->t[0]!='\0'){
							if(strcmp(p_func_invocation.arguments[i]->t,s[i])!=0){
								has_error=true;	
								error_handle e;
								e.line=p_func_invocation.arguments[i]->getLocation().line;
								e.col=p_func_invocation.arguments[i]->getLocation().col;
								sprintf(e.str,"<Error> Found in line %d, column %d: incompatible type passing '%s' to parameter of type '%s'",e.line,e.col,p_func_invocation.arguments[i]->t,s[i]);
								er.push_back(e);
								err=false;
							}
						}
						else{
							has_error=true;	
							error_handle e;
							e.line=p_func_invocation.arguments[i]->getLocation().line;
							e.col=p_func_invocation.arguments[i]->getLocation().col;
							sprintf(e.str,"<Error> Found in line %d, column %d: incompatible type passing '%s' to parameter of type '%s'",e.line,e.col,cm,s[i]);
							er.push_back(e);
							err=false;
						}
	
					}
				}
			}
	
		}
		if(err){
			if (strstr(ma.find_fun_return_type(p_func_invocation.getNameCString()),"integer")!=NULL) {
				//auto *p=new PType(PType::PrimitiveTypeEnum::kIntegerType);
				p_func_invocation.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kIntegerType);
				p_func_invocation.dim=0;
				strcpy(p_func_invocation.t,ma.find_fun_return_type(p_func_invocation.getNameCString()));
				//printf("%d\n",d);
			}
			else if (strstr(ma.find_fun_return_type(p_func_invocation.getNameCString()),"real")!=NULL) {
				p_func_invocation.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kRealType);
				p_func_invocation.dim=0;
				strcpy(p_func_invocation.t,ma.find_fun_return_type(p_func_invocation.getNameCString()));
			}
			else if (strstr(ma.find_fun_return_type(p_func_invocation.getNameCString()),"string")!=NULL) {
				p_func_invocation.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kStringType);
				p_func_invocation.dim=0;
				strcpy(p_func_invocation.t,ma.find_fun_return_type(p_func_invocation.getNameCString()));
			}
			else if (strstr(ma.find_fun_return_type(p_func_invocation.getNameCString()),"boolean")!=NULL) {
				p_func_invocation.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kBoolType);
				p_func_invocation.dim=0;
				strcpy(p_func_invocation.t,ma.find_fun_return_type(p_func_invocation.getNameCString()));
			}
			else if (strstr(ma.find_fun_return_type(p_func_invocation.getNameCString()),"void")!=NULL) {
				p_func_invocation.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kVoidType);
				p_func_invocation.dim=0;
				strcpy(p_func_invocation.t,ma.find_fun_return_type(p_func_invocation.getNameCString()));
			}
		}	
	}
	else{
		if(ma.find_var(p_func_invocation.getNameCString())){
			has_error=true;	
			error_handle e;
			e.line=p_func_invocation.getLocation().line;
			e.col=p_func_invocation.getLocation().col;
			sprintf(e.str,"<Error> Found in line %d, column %d: call of non-function symbol '%s'",e.line,e.col,p_func_invocation.getNameCString());
			er.push_back(e);
		}
		else{
			has_error=true;	
			error_handle e;
			e.line=p_func_invocation.getLocation().line;
			e.col=p_func_invocation.getLocation().col;
			sprintf(e.str,"<Error> Found in line %d, column %d: use of undeclared symbol '%s'",e.line,e.col,p_func_invocation.getNameCString());
			er.push_back(e);
		}
	}

}

void SemanticAnalyzer::visit(VariableReferenceNode &p_variable_ref) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
	if(ma.check_not_decl(p_variable_ref.getNameCString())){
		has_error=true;	
		error_handle e;
		e.line=p_variable_ref.getLocation().line;
		e.col=p_variable_ref.getLocation().col;
		sprintf(e.str,"<Error> Found in line %d, column %d: use of undeclared symbol '%s'",e.line,e.col,p_variable_ref.getNameCString());
		er.push_back(e);
	}
	else if(ma.check_not_use_var(p_variable_ref.getNameCString())){
		has_error=true;	
		error_handle e;
		e.line=p_variable_ref.getLocation().line;
		e.col=p_variable_ref.getLocation().col;
		sprintf(e.str,"<Error> Found in line %d, column %d: use of non-variable symbol '%s'",e.line,e.col,p_variable_ref.getNameCString());
		er.push_back(e);
	}
	else {
		bool ch=true;
		if(ma.find_var(p_variable_ref.getNameCString())){
			p_variable_ref.visitChildNodes(*this);
			
			for(int i=0;i<p_variable_ref.indices.size();i++){
				if(p_variable_ref.indices[i]->type!=NULL){
					if(p_variable_ref.indices[i]->type->getPrimitiveType()!=PType::PrimitiveTypeEnum::kIntegerType){
						has_error=true;	
						error_handle e;
						e.line=p_variable_ref.indices[i]->getLocation().line;
						e.col=p_variable_ref.indices[i]->getLocation().col;
						sprintf(e.str,"<Error> Found in line %d, column %d: index of array reference must be an integer",e.line,e.col);
						er.push_back(e);
						ch=false;
					}
				}
			}
			if(ch){
				if(p_variable_ref.indices.size()>ma.find_var_ptype_num(p_variable_ref.getNameCString())){
					has_error=true;	
					error_handle e;
					e.line=p_variable_ref.getLocation().line;
					e.col=p_variable_ref.getLocation().col;
					sprintf(e.str,"<Error> Found in line %d, column %d: there is an over array subscript on '%s'",e.line,e.col,p_variable_ref.getNameCString());
					er.push_back(e);
				}
				else{
					//printf("%d\n",ma.find_var_ptype_num(p_variable_ref.getNameCString()));
					//printf("%d\n",p_variable_ref.indices.size());
					if (strstr(ma.find_var_type(p_variable_ref.getNameCString()),"integer")!=NULL) {
						//auto *p=new PType(PType::PrimitiveTypeEnum::kIntegerType);
						p_variable_ref.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kIntegerType);
						int d=ma.find_var_ptype_num(p_variable_ref.getNameCString())-p_variable_ref.indices.size();
						p_variable_ref.dim=d;
						strcpy(p_variable_ref.t,ma.find_var_type(p_variable_ref.getNameCString()));
						//printf("%d\n",d);
					}
					else if (strstr(ma.find_var_type(p_variable_ref.getNameCString()),"real")!=NULL) {
						p_variable_ref.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kRealType);
						int d=ma.find_var_ptype_num(p_variable_ref.getNameCString())-p_variable_ref.indices.size();
						p_variable_ref.dim=d;
						strcpy(p_variable_ref.t,ma.find_var_type(p_variable_ref.getNameCString()));
					}
					else if (strstr(ma.find_var_type(p_variable_ref.getNameCString()),"string")!=NULL) {
						p_variable_ref.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kStringType);
						int d=ma.find_var_ptype_num(p_variable_ref.getNameCString())-p_variable_ref.indices.size();
						p_variable_ref.dim=d;
						strcpy(p_variable_ref.t,ma.find_var_type(p_variable_ref.getNameCString()));
					}
					else if (strstr(ma.find_var_type(p_variable_ref.getNameCString()),"boolean")!=NULL) {
						p_variable_ref.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kBoolType);
						int d=ma.find_var_ptype_num(p_variable_ref.getNameCString())-p_variable_ref.indices.size();
						p_variable_ref.dim=d;
						strcpy(p_variable_ref.t,ma.find_var_type(p_variable_ref.getNameCString()));
					}
					else if (strstr(ma.find_var_type(p_variable_ref.getNameCString()),"void")!=NULL) {
						p_variable_ref.type=std::make_shared<PType>(PType::PrimitiveTypeEnum::kVoidType);
						int d=ma.find_var_ptype_num(p_variable_ref.getNameCString())-p_variable_ref.indices.size();
						p_variable_ref.dim=d;
						strcpy(p_variable_ref.t,ma.find_var_type(p_variable_ref.getNameCString()));
					}
				}
			}
		}
	}	
}

void SemanticAnalyzer::visit(AssignmentNode &p_assignment) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
	p_assignment.visitChildNodes(*this);
	
	if(p_assignment.lvalue!=NULL){
		if(p_assignment.lvalue->dim!=0){
			has_error=true;	
			error_handle e;
			e.line=p_assignment.lvalue->getLocation().line;
			e.col=p_assignment.lvalue->getLocation().col;
			sprintf(e.str,"<Error> Found in line %d, column %d: array assignment is not allowed",e.line,e.col);
			er.push_back(e);	
		}
		else if(ma.find_var_kind(p_assignment.lvalue->getNameCString())!=NULL){
			if(strcmp(ma.find_var_kind(p_assignment.lvalue->getNameCString()),"constant")==0){
				has_error=true;	
				error_handle e;
				e.line=p_assignment.lvalue->getLocation().line;
				e.col=p_assignment.lvalue->getLocation().col;
				sprintf(e.str,"<Error> Found in line %d, column %d: cannot assign to variable '%s' which is a constant",e.line,e.col,p_assignment.lvalue->getNameCString());
				er.push_back(e);
			}
			else if(in_for_assign==false){ 
				if(strcmp(ma.find_var_kind(p_assignment.lvalue->getNameCString()),"loop_var")==0){
					has_error=true;	
					error_handle e;
					e.line=p_assignment.lvalue->getLocation().line;
					e.col=p_assignment.lvalue->getLocation().col;
					sprintf(e.str,"<Error> Found in line %d, column %d: the value of loop variable cannot be modified inside the loop body",e.line,e.col);
					er.push_back(e);
				}
				else{
					char n[50],m[50];

					if(p_assignment.lvalue->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kIntegerType) strcpy(n,"integer");
					else if(p_assignment.lvalue->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kRealType) strcpy(n,"real");
					else if(p_assignment.lvalue->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kStringType) strcpy(n,"string");
					else if(p_assignment.lvalue->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kBoolType) strcpy(n,"boolean");
					else if(p_assignment.lvalue->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kVoidType) strcpy(n,"void");
					if(p_assignment.expr->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kIntegerType) strcpy(m,"integer");
					else if(p_assignment.expr->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kRealType) strcpy(m,"real");
					else if(p_assignment.expr->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kStringType) strcpy(m,"string");
					else if(p_assignment.expr->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kBoolType) strcpy(m,"boolean");
					else if(p_assignment.expr->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kVoidType) strcpy(m,"void");

					if((strcmp(n,"integer")==0||strcmp(n,"real")==0)&&(strcmp(m,"integer")==0||strcmp(m,"real")==0)){
						if(p_assignment.expr->dim!=0){
							has_error=true;	
							error_handle e;
							e.line=p_assignment.expr->getLocation().line;
							e.col=p_assignment.expr->getLocation().col;
							sprintf(e.str,"<Error> Found in line %d, column %d: array assignment is not allowed",e.line,e.col);
							er.push_back(e);
						}
					}
					else if(strcmp(n,m)==0){
						if(p_assignment.expr->dim!=0){
							has_error=true;	
							error_handle e;
							e.line=p_assignment.expr->getLocation().line;
							e.col=p_assignment.expr->getLocation().col;
							sprintf(e.str,"<Error> Found in line %d, column %d: array assignment is not allowed",e.line,e.col);
							er.push_back(e);
						}
					}
					else{
						has_error=true;	
						error_handle e;
						e.line=p_assignment.getLocation().line;
						e.col=p_assignment.getLocation().col;
						sprintf(e.str,"<Error> Found in line %d, column %d: assigning to '%s' from incompatible type '%s'",e.line,e.col,n,m);
						er.push_back(e);
					}		
				}
			}
			
		}
	}
	in_for_assign=false;

}

void SemanticAnalyzer::visit(ReadNode &p_read) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
	p_read.visitChildNodes(*this);
	if(p_read.target!=NULL&&p_read.target->dim!=0){
		has_error=true;	
		error_handle e;
		e.line=p_read.target->getLocation().line;
		e.col=p_read.target->getLocation().col;
		sprintf(e.str,"<Error> Found in line %d, column %d: variable reference of read statement must be scalar type",e.line,e.col);
		er.push_back(e);	
	}
	else{
		const char *s=p_read.target->name.c_str();
		//printf("%s\n",s);
		if(ma.find_var_kind(s)!=NULL){
			if(strcmp(ma.find_var_kind(s),"loop_var")==0||strcmp(ma.find_var_kind(s),"constant")==0){
				has_error=true;	
				error_handle e;
				e.line=p_read.target->getLocation().line;
				e.col=p_read.target->getLocation().col;
				sprintf(e.str,"<Error> Found in line %d, column %d: variable reference of read statement cannot be a constant or loop variable",e.line,e.col);
				er.push_back(e);
			}
		}
	}
}


void SemanticAnalyzer::visit(IfNode &p_if) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
	p_if.visitChildNodes(*this);
	if(p_if.condition->type!=NULL){
		if(p_if.condition->type->getPrimitiveType()!=PType::PrimitiveTypeEnum::kBoolType||p_if.condition->dim!=0){
			has_error=true;	
			error_handle e;
			e.line=p_if.condition->getLocation().line;
			e.col=p_if.condition->getLocation().col;
			sprintf(e.str,"<Error> Found in line %d, column %d: the expression of condition must be boolean type",e.line,e.col);
			er.push_back(e);
		}
	}


}

void SemanticAnalyzer::visit(WhileNode &p_while) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
	p_while.visitChildNodes(*this);
	if(p_while.condition->type!=NULL){
		if(p_while.condition->type->getPrimitiveType()!=PType::PrimitiveTypeEnum::kBoolType||p_while.condition->dim!=0){
			has_error=true;	
			error_handle e;
			e.line=p_while.condition->getLocation().line;
			e.col=p_while.condition->getLocation().col;
			sprintf(e.str,"<Error> Found in line %d, column %d: the expression of condition must be boolean type",e.line,e.col);
			er.push_back(e);
		}
	}
}

void SemanticAnalyzer::visit(ForNode &p_for) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
	SymbolTable *new_scope=new SymbolTable;
	ma.pushScope(new_scope);
	need_var=true;
	in_for_assign=true;
	need_for_init=true;
	p_for.visitChildNodes(*this);
	
	int l,r;
	//if(p_for.initial_statement->expr->constant!=NULL){
	//	printf("%s\n",p_for.initial_statement->expr->constant->getConstantValueCString());
	//}
	l=atoi(for_init);
	r=atoi(p_for.condition->getConstantValueCString());
	//printf("123 %s\n",for_init);
	//printf("%d %d\n",l,r);
	if(l>=r){
		has_error=true;	
		error_handle e;
		e.line=p_for.getLocation().line;
		e.col=p_for.getLocation().col;
		sprintf(e.str,"<Error> Found in line %d, column %d: the lower bound and upper bound of iteration count must be in the incremental order",e.line,e.col);
		er.push_back(e);
	}

	if(turndump) ma.print_top();
	ma.free_top();
	ma.popScope();
}

void SemanticAnalyzer::visit(ReturnNode &p_return) {
    /*
     * TODO:
     *
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration (ProgramNode, VariableNode, FunctionNode).
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
	p_return.visitChildNodes(*this);
	if(strcmp(ma.find_p_and_f_return_type(fun[fun.size()-1].c_str()),"void")==0){
		has_error=true;	
		error_handle e;
		e.line=p_return.getLocation().line;
		e.col=p_return.getLocation().col;
		sprintf(e.str,"<Error> Found in line %d, column %d: program/procedure should not return a value",e.line,e.col);
		er.push_back(e);
	}
	else{
		if(p_return.retval->type!=NULL){
			char n[50],m[50];
			strcpy(m,ma.find_p_and_f_return_type(fun[fun.size()-1].c_str()));
			if(p_return.retval->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kIntegerType) strcpy(n,"integer");
			else if(p_return.retval->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kRealType) strcpy(n,"real");
			else if(p_return.retval->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kStringType) strcpy(n,"string");
			else if(p_return.retval->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kBoolType) strcpy(n,"boolean");
			else if(p_return.retval->type->getPrimitiveType()==PType::PrimitiveTypeEnum::kVoidType) strcpy(n,"void");

			if(p_return.retval->dim!=0){
				int i,j;
				i=0;
				while(p_return.retval->t[i]!='\0'){
					i++;
				}
				i--;
				int c=p_return.retval->dim;
				char a[50],b[50];
				j=0;
				//printf("%d\n",c);
				while(c!=0){
					a[j]=p_return.retval->t[i];
					i--;
					j++;
					if(p_return.retval->t[i]=='['){
						c--;
					}
				}
				a[j]=p_return.retval->t[i];
				a[j+1]='\0';
				//printf("%s\n",a);
				i=0;
				while(j>=0){
					b[i]=a[j];
					i++;
					j--;
				}
				b[i]='\0';
				strcat(n," ");
				strcat(n,b);
				//printf("%s\n",b);
			}
			if(strcmp(n,m)!=0){
				has_error=true;	
				error_handle e;
				e.line=p_return.retval->getLocation().line;
				e.col=p_return.retval->getLocation().col;
				sprintf(e.str,"<Error> Found in line %d, column %d: return '%s' from a function with return type '%s'",e.line,e.col,n,m);
				er.push_back(e);
			}
			//printf("%d\n",p_return.retval->dim);
			//printf("%s\n",p_return.retval->t);
		}
	}
}
