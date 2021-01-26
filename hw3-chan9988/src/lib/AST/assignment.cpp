#include "AST/assignment.hpp"

// TODO
AssignmentNode::AssignmentNode(const uint32_t line, const uint32_t col,AstNode*vr,AstNode *ex)
    : AstNode{line, col},vr(vr),ex(ex) {}

// TODO: You may use code snippets in AstDumper.cpp
void AssignmentNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	std::printf("assignment statement <line: %u, col: %u>\n",location.line,location.col);
	if(vr!=NULL) vr->print();
	if(ex!=NULL) ex->print();
	tab--;
}

// void AssignmentNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
