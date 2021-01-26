#ifndef __AST_UNARY_OPERATOR_NODE_H
#define __AST_UNARY_OPERATOR_NODE_H

#include "AST/expression.hpp"
#include "AST/AstDumper.hpp"

class UnaryOperatorNode : public ExpressionNode {
  public:
    UnaryOperatorNode(const uint32_t line, const uint32_t col,char *op,AstNode *ex1);
    ~UnaryOperatorNode() = default;

    void print() override;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};

	void visitChildNodes(AstNodeVisitor &v){
		if(ex1!=NULL) ex1->accept(v);
	};

  //private:
    // TODO: operator, expression
	char *op;
	AstNode *ex1=NULL;
};

#endif
