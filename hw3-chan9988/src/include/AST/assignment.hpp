#ifndef __AST_ASSIGNMENT_NODE_H
#define __AST_ASSIGNMENT_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"

class AssignmentNode : public AstNode {
  public:
    AssignmentNode(const uint32_t line, const uint32_t col,AstNode *vr,AstNode *ex);
    ~AssignmentNode() = default;

    void print() override;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};
	void visitChildNodes(AstNodeVisitor &v){
		if(vr!=NULL) vr->accept(v);
		if(ex!=NULL) ex->accept(v);
	}
  //private:
    // TODO: variable reference, expression
	AstNode *vr=NULL;
	AstNode *ex=NULL;
};

#endif
