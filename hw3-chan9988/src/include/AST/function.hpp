#ifndef __AST_FUNCTION_NODE_H
#define __AST_FUNCTION_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"

class FunctionNode : public AstNode {
  public:
    FunctionNode(const uint32_t line, const uint32_t col,char *name,int returntype);
    ~FunctionNode() = default;

    void print() override;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};

	void visitChildNodes(AstNodeVisitor &v){
		for (auto i: decl){
			i->accept(v);
		}
		if(ch!=NULL) ch->accept(v);

	};

	void add_de(AstNode *);
	void add_arg(int);
	void add_compoundstatement(AstNode *);

  //private:
    // TODO: name, declarations, return type, compound statement
	char *name;
	std::vector<AstNode *> decl;
	int returntype;    // 4==> NULL
	std::vector<int> arg;   // argument type 
	AstNode *ch=NULL;
};

#endif
