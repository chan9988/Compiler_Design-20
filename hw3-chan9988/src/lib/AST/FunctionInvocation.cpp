#include "AST/FunctionInvocation.hpp"

// TODO
FunctionInvocationNode::FunctionInvocationNode(const uint32_t line,
                                               const uint32_t col,char *name)
    : ExpressionNode{line, col},name(name) {}

// TODO: You may use code snippets in AstDumper.cpp
void FunctionInvocationNode::print() {
	tab++;
	int t=tab;	
	while(t--){
		printf("  ");
	}
	printf("function invocation <line: %d, col: %d> %s\n",location.line,location.col,name);
	if(ch.size()>0){
		for (auto i: ch){
			i->print();
		}
	}
	tab--;
}
void FunctionInvocationNode::add_child(AstNode *n){
	ch.push_back(n);
}

// void FunctionInvocationNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
