#include "AST/decl.hpp"

// TODO
DeclNode::DeclNode(const uint32_t line, const uint32_t col)
    : AstNode{line, col} {}

// TODO
//DeclNode::DeclNode(const uint32_t line, const uint32_t col)
//    : AstNode{line, col} {}

// TODO: You may use code snippets in AstDumper.cpp
void DeclNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	printf("declaration <line: %u, col: %u>\n",location.line,location.col);
	for (auto i: ch){
		i->print();
	}
	tab--;
}

void DeclNode::add_child(AstNode *n){
	ch.push_back(n);
}

// void DeclNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
