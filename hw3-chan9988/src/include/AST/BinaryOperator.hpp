#ifndef __AST_BINARY_OPERATOR_NODE_H
#define __AST_BINARY_OPERATOR_NODE_H

#include "AST/expression.hpp"
#include "AST/AstDumper.hpp"

#include <memory>

class BinaryOperatorNode : public ExpressionNode {
  public:
    BinaryOperatorNode(const uint32_t line, const uint32_t col,char *op,AstNode *ex1,AstNode *ex2);
    ~BinaryOperatorNode() = default;

    void print() override;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};

	void visitChildNodes(AstNodeVisitor &v){
		if(ex1!=NULL) ex1->accept(v);
		if(ex2!=NULL) ex2->accept(v);
	};

  //private:
    // TODO: operator, expressions
	char *op;
	AstNode *ex1;
	AstNode *ex2;
};

#endif
