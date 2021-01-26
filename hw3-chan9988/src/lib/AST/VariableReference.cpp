#include "AST/VariableReference.hpp"

// TODO
VariableReferenceNode::VariableReferenceNode(const uint32_t line,
                                             const uint32_t col,char *name)
    : ExpressionNode{line, col},name(name) {}

// TODO
// VariableReferenceNode::VariableReferenceNode(const uint32_t line,
//                                              const uint32_t col)
//     : ExpressionNode{line, col} {}

// TODO: You may use code snippets in AstDumper.cpp
void VariableReferenceNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	printf("variable reference <line: %d, col: %d> %s\n",location.line,location.col,name);
	if(ex.size()>0){
		for (auto i: ex){
			i->print();
		}
	}
	tab--;
}

void VariableReferenceNode::add_child(AstNode *ch){
	ex.push_back(ch);
}

// void VariableReferenceNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
