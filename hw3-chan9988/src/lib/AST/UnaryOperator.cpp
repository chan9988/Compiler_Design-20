#include "AST/UnaryOperator.hpp"

// TODO
UnaryOperatorNode::UnaryOperatorNode(const uint32_t line, const uint32_t col,char *op,AstNode *ex1)
    : ExpressionNode{line, col},op(op),ex1(ex1) {}

// TODO: You may use code snippets in AstDumper.cpp
void UnaryOperatorNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	printf("unary operator <line: %d, col: %d> %s\n",location.line,location.col,op);
	ex1->print();
	tab--;
}

// void UnaryOperatorNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
