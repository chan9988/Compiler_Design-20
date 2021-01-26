#include "AST/while.hpp"

// TODO
WhileNode::WhileNode(const uint32_t line, const uint32_t col,AstNode *ex,AstNode *cs)
    : AstNode{line, col},ex(ex),cs(cs) {}

// TODO: You may use code snippets in AstDumper.cpp
void WhileNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	printf("while statement <line: %d, col: %d>\n",location.line,location.col);
	if(ex!=NULL) ex->print();
	if(cs!=NULL) cs->print();
	tab--;
}

// void WhileNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
