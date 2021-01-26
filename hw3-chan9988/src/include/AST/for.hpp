#ifndef __AST_FOR_NODE_H
#define __AST_FOR_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"

class ForNode : public AstNode {
  public:
    ForNode(const uint32_t line, const uint32_t col,AstNode *de,AstNode *as,AstNode *ex,AstNode *cs);
    ~ForNode() = default;

    void print() override;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};

	void visitChildNodes(AstNodeVisitor &v){
		if(de!=NULL) de->accept(v);
		if(as!=NULL) as->accept(v);
		if(ex!=NULL) ex->accept(v);
		if(cs!=NULL) cs->accept(v);
	};

  //private:
    // TODO: declaration, assignment, expression, compound statement
	AstNode *de;
	AstNode *as;
	AstNode *ex;
	AstNode *cs;
};

#endif
