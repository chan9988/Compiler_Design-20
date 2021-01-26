#include "AST/BinaryOperator.hpp"

// TODO
BinaryOperatorNode::BinaryOperatorNode(const uint32_t line, const uint32_t col,char *op,AstNode *ex1,AstNode *ex2): ExpressionNode{line, col},op(op),ex1(ex1),ex2(ex2) {}

// TODO: You may use code snippets in AstDumper.cpp
void BinaryOperatorNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	printf("binary operator <line: %d, col: %d> %s\n",location.line,location.col,op);
	ex1->print();
	ex2->print();
	tab--;
}

// void BinaryOperatorNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
