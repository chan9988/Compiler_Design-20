#include "AST/return.hpp"

// TODO
ReturnNode::ReturnNode(const uint32_t line, const uint32_t col,AstNode *ex)
    : AstNode{line, col},ex(ex) {}

// TODO: You may use code snippets in AstDumper.cpp
void ReturnNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	printf("return statement <line: %d, col: %d>\n",location.line,location.col);
	if(ex!=NULL) ex->print();
	tab--;
}

// void ReturnNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
