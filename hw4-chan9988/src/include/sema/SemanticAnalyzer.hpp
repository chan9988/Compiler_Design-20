#ifndef __SEMA_SEMANTIC_ANALYZER_H
#define __SEMA_SEMANTIC_ANALYZER_H

#include "visitor/AstNodeVisitor.hpp"
#include <stack>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>

class error_handle{
public:
	char str[512];
	int line;
	int col;

};

class SymbolEntry {
public:
//private:
    // Variable names
    // Kind
    // Level
    // ...
	const char *name;
	const char *kind;
	const char *type;
	//int type_value;  // 0=>void 1=>int 2=>real 3=>boolean 4=>string
	//bool has_attribute;
	//int int_value;
	//double real_value;
	//char *bool_value;
	//char *string_value;
	const char *attribute;
	int n_ptype=0;
	bool valid=true;
};

class SymbolTable {
public:
    void addSymbol(SymbolEntry new_entry){
		entries.push_back(new_entry);
	}
    // other methods
//private:
    std::vector<SymbolEntry> entries;
};


class SymbolManager {
public:
    void pushScope(SymbolTable *new_scope){
		tables.push_back(new_scope);
		//std::cout << tables.size() << std::endl;
	}
    void popScope(){
		tables.pop_back();
	}
	// other methods
	void free_top(){
		free(tables[tables.size()-1]);
	}
	void pushentry(SymbolEntry new_entry){
		tables[tables.size()-1]->addSymbol(new_entry);
	}

	bool check_decl(const char *s){
		bool ch=false;
		for(auto i:tables[tables.size()-1]->entries){
			if(strcmp(s,i.name)==0) ch=true;
			if(ch) return ch;
		}
		for(int i=0;i<tables.size();i++){
			for(auto j:tables[i]->entries){
				if(strcmp(s,j.name)==0&&strcmp(j.kind,"loop_var")==0) ch=true;
				if(ch) return ch;
			}
		}
		return ch;
	}
	
	bool check_not_decl(const char *s){
		bool ch=true;
		for(auto i:tables[tables.size()-1]->entries){
			if(strcmp(s,i.name)==0) ch=false;
		}
		for(int i=0;i<tables.size();i++){
			for(auto j:tables[i]->entries){
				if(strcmp(s,j.name)==0) ch=false;
			}
		}
		return ch;
	}

	bool find_var(const char *s){
		bool ch=false;
		for(auto i:tables[tables.size()-1]->entries){
			if(strcmp(s,i.name)==0&&i.valid==true) ch=true;
		}
		for(int i=0;i<tables.size();i++){
			for(auto j:tables[i]->entries){
				if(strcmp(s,j.name)==0&&j.valid==true) ch=true;
			}
		}
		return ch;
	}

	bool var_in_for_init(const char *s){
		//bool ch=false;
		if(tables[tables.size()-1]->entries.size()==1){
			/*
			for(auto i:tables[tables.size()-1]->entries){
				if(strcmp(s,i.name)==0&&i.valid==true) ch=true;
			}
			*/
			return true;
		}
		return false;
	}

	const char * find_var_type(const char *s){
		for(int i=tables.size()-1;i>=0;i--){
			for(auto j:tables[i]->entries){
				if(strcmp(s,j.name)==0&&j.valid==true) return j.type; 	
			}
		}
		return NULL;
	}

	const char * find_fun_return_type(const char *s){
		for(int i=tables.size()-1;i>=0;i--){
			for(auto j:tables[i]->entries){
				if(strcmp(s,j.name)==0&&strcmp(j.kind,"function")==0&&j.valid==true) return j.type; 	
			}
		}
		return NULL;
	}

	const char * find_p_and_f_return_type(const char *s){
		for(int i=tables.size()-1;i>=0;i--){
			for(auto j:tables[i]->entries){
				if(strcmp(s,j.name)==0&&(strcmp(j.kind,"function")==0||strcmp(j.kind,"program")==0)&&j.valid==true) return j.type; 	
			}
		}
		return NULL;
	}

	const char * find_fun_attr(const char *s){
		for(int i=tables.size()-1;i>=0;i--){
			for(auto j:tables[i]->entries){
				if(strcmp(s,j.name)==0&&strcmp(j.kind,"function")==0&&j.valid==true) return j.attribute; 	
			}
		}
		return NULL;
	}

	const char * find_var_kind(const char *s){
		for(int i=tables.size()-1;i>=0;i--){
			for(auto j:tables[i]->entries){
				if(strcmp(s,j.name)==0&&j.valid==true) return j.kind; 	
			}
		}
		return NULL;
	}

	bool check_not_use_var(const char *s){
		bool ch=true;
		for(auto i:tables[tables.size()-1]->entries){
			if(strcmp(s,i.name)==0&&strcmp(i.kind,"function")!=0) ch=false;
		}
		for(int i=0;i<tables.size();i++){
			for(auto j:tables[i]->entries){
				if(strcmp(s,j.name)==0&&strcmp(j.kind,"function")!=0) ch=false;
			}
		}
		return ch;
	}

	int find_var_ptype_num(const char *s){
		for(int i=tables.size()-1;i>=0;i--){
			for(auto j:tables[i]->entries){
				if(strcmp(s,j.name)==0&&j.valid==true) return j.n_ptype; 	
			}
		}
		return 0;
	}

	void print_top(){
		dumpSymbol();
	}

	void dumpDemarcation(const char chr) {
		for (size_t i = 0; i < 110; ++i) {
			printf("%c", chr);
		}
		puts("");
	}
	void dumpSymbol(void) {
		dumpDemarcation('=');
		printf("%-33s%-11s%-11s%-17s%-11s\n", "Name","Kind","Level","Type","Attribute");
		dumpDemarcation('-');
	{
		for(auto i:tables[tables.size()-1]->entries){
			printf("%-33s", i.name);
			printf("%-11s", i.kind);
			if(tables.size()-1==0) printf("%d%-10s", tables.size()-1, "(global)");
			else printf("%d%-10s", tables.size()-1, "(local)");			
			printf("%-17s", i.type);
			if(i.attribute!=NULL) printf("%-11s", i.attribute);
			puts("");
		}
	}
  		dumpDemarcation('-');
	}

//private:
    std::vector <SymbolTable *> tables;
};


class SemanticAnalyzer : public AstNodeVisitor {
  public:
    SemanticAnalyzer() = default;
    ~SemanticAnalyzer() = default;

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

  //private:
    // TODO: something like symbol manager (manage symbol tables)
    //       context manager, return type manager
	SymbolManager ma;
	bool need_cs=false;
	bool need_var=false;
	bool need_par=false;
	bool has_error=false;
	bool write_to_var=false;
	bool in_for_assign=false;
	std::vector<error_handle> er;
	bool turndump=true;
	char for_init[50];
	bool need_for_init=false;
	std::vector<std::string> fun;
};

#endif
