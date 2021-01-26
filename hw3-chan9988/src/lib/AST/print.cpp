#include "AST/print.hpp"

// TODO
PrintNode::PrintNode(const uint32_t line, const uint32_t col,AstNode *ch)
    : AstNode{line, col},ch(ch) {}

// TODO: You may use code snippets in AstDumper.cpp
void PrintNode::print() {
	//printf("test");
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	printf("print statement <line: %u, col: %u>\n",location.line,location.col);
	ch->print();
	tab--;

}

// void PrintNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
