#include "AST/CompoundStatement.hpp"

// TODO
CompoundStatementNode::CompoundStatementNode(const uint32_t line,
                                             const uint32_t col)
    : AstNode{line, col} {}

// TODO: You may use code snippets in AstDumper.cpp
void CompoundStatementNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	printf("compound statement <line: %u, col: %u>\n",location.line,location.col);
	if(decl.size()!=0){	
		for(auto i: decl){
			i->print();
		}
	}
	if(stat.size()!=0){	
		for(auto i: stat){
			i->print();
		}
	}
	tab--;
}

void CompoundStatementNode::add_de(AstNode *n){
	decl.push_back(n);
}

void CompoundStatementNode::add_st(AstNode *n){
	if(n!=NULL)
		stat.push_back(n);
}

// void CompoundStatementNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
