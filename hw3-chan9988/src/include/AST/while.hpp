#ifndef __AST_WHILE_NODE_H
#define __AST_WHILE_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"

class WhileNode : public AstNode {
  public:
    WhileNode(const uint32_t line, const uint32_t col
              /* TODO: expression, compound statement */,AstNode *ex,AstNode *cs);
    ~WhileNode() = default;

    void print() override;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};

	void visitChildNodes(AstNodeVisitor &v){
		if(ex!=NULL) ex->accept(v);
		if(cs!=NULL) cs->accept(v);

	};

  //private:
    // TODO: expression, compound statement
	AstNode *ex;
	AstNode *cs;
};

#endif
