#ifndef __CODE_GENERATOR_H
#define __CODE_GENERATOR_H

#include "sema/SymbolTable.hpp"
#include "visitor/AstNodeVisitor.hpp"

class CodeGenerator : public AstNodeVisitor {
  public:
    CodeGenerator(const char *in_file_name, const char *out_file_name, SymbolManager *symbol_manager);
    ~CodeGenerator();

    void dumpInstrs(const char *format, ...);

    void visit(ProgramNode &p_program) override;
    void visit(DeclNode &p_decl) override;
    void visit(VariableNode &p_variable) override;
    void visit(ConstantValueNode &p_constant_value) override;
    void visit(FunctionNode &p_function) override;
    void visit(CompoundStatementNode &p_compound_statement) override;
    void visit(PrintNode &p_print) override;
    void visit(BinaryOperatorNode &p_bin_op) override;
    void visit(UnaryOperatorNode &p_un_op) override;
    void visit(FunctionInvocationNode &p_func_invocation) override;
    void visit(VariableReferenceNode &p_variable_ref) override;
    void visit(AssignmentNode &p_assignment) override;
    void visit(ReadNode &p_read) override;
    void visit(IfNode &p_if) override;
    void visit(WhileNode &p_while) override;
    void visit(ForNode &p_for) override;
    void visit(ReturnNode &p_return) override;
    void add_var(std::string s){
      va.push_back(make_pair(dep,make_pair(s,offset)));
      std::vector<int> a;
      ind.push_back(make_pair(dep,make_pair(s,a)));
    }
    int find_var(std::string s){
      for(int i=va.size()-1;i>=0;i--){
        if(va[i].second.first==s){
          return va[i].second.second;
        }
      }
      return 0;
    }
    void add_ind(std::string s,int d){
      for(int i=ind.size()-1;i>=0;i--){
        if(ind[i].second.first==s){
          ind[i].second.second.push_back(d);
          return;
        }
      }
    }
    std::vector<int> &find_ind(std::string s){
      for(int i=ind.size()-1;i>=0;i--){
        if(ind[i].second.first==s){
          return ind[i].second.second;
        }
      }
    }
    void popvar(){
      //dumpInstrs("%d\n\n\n",va.size()-1);
      for(int i=va.size()-1;i>=0;i--){
        if(va[i].first==dep){
          va.pop_back();
        }
        else{
          break;
        }
      }
      for(int i=ind.size()-1;i>=0;i--){
        if(ind[i].first==dep){
          ind.pop_back();
        }
        else{
          break;
        }
      }
    }

    int find_dec_var(std::string s){
      for(int i=0;i<dec_var.size();i++){
        if(dec_var[i].first==s){
          return dec_var[i].second;
        }
      }
      return 0;
    }

  private:
    const char *in_file_name;
    FILE *out_fp;
    SymbolManager *symbol_manager;
    int dep=0;
    int offset=-12;
    std::vector<int> off;
    bool re=false;
    int le=1;
    int arg=0;
    bool co_str=false;
    bool co_flo=false;
    bool pu_flo=false;
    bool bo_ass=false;
    bool in_cond=false;
    bool in_cond_var=false;
    std::vector<std::pair<std::string,int> > dec_var;  // 1 2 3 => float string boolean
    std::vector< std::pair<int,std::pair<std::string,int> > > va;
    std::vector< std::pair<int,std::pair<std::string,std::vector<int> > > > ind;
    std::vector< std::string > la;
};

#endif