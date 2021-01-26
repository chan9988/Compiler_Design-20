#include "AST/for.hpp"

// TODO
ForNode::ForNode(const uint32_t line, const uint32_t col,AstNode *de,AstNode *as,AstNode *ex,AstNode *cs)
    : AstNode{line, col},de(de),as(as),ex(ex),cs(cs) {}

// TODO: You may use code snippets in AstDumper.cpp
void ForNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	printf("for statement <line: %d, col: %d>\n",location.line,location.col);
	if(de!=NULL) de->print();
	if(as!=NULL) as->print();
	if(ex!=NULL) ex->print();
	if(cs!=NULL) cs->print();
	tab--;    
}

// void ForNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
