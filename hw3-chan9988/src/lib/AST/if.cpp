#include "AST/if.hpp"

// TODO
IfNode::IfNode(const uint32_t line, const uint32_t col,AstNode *ex,AstNode *cs1,AstNode *cs2)
    : AstNode{line, col},ex(ex),cs1(cs1),cs2(cs2) {}

// TODO: You may use code snippets in AstDumper.cpp
void IfNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	printf("if statement <line: %d, col: %d>\n",location.line,location.col);
	if(ex!=NULL) ex->print();
	if(cs1!=NULL) cs1->print();
	if(cs2!=NULL) cs2->print();
	tab--;
}

// void IfNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
