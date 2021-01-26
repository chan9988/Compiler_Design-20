#include "AST/read.hpp"

// TODO
ReadNode::ReadNode(const uint32_t line, const uint32_t col,AstNode *vr)
    : AstNode{line, col},vr(vr) {}

// TODO: You may use code snippets in AstDumper.cpp
void ReadNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	printf("read statement <line: %d, col: %d>\n",location.line,location.col);
	vr->print();	
	tab--;
}

// void ReadNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
