#ifndef __AST_IF_NODE_H
#define __AST_IF_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"

class IfNode : public AstNode {
  public:
    IfNode(const uint32_t line, const uint32_t col,AstNode *ex,AstNode *cs1,AstNode* cs2);
    ~IfNode() = default;

    void print() override;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};

	void visitChildNodes(AstNodeVisitor &v){
		if(ex!=NULL) ex->accept(v);
		if(cs1!=NULL) cs1->accept(v);
		if(cs2!=NULL) cs2->accept(v);
	};

  //private:
    // TODO: expression, compound statement, compound statement
	AstNode *ex=NULL;
	AstNode *cs1=NULL;
	AstNode *cs2=NULL;
};

#endif
