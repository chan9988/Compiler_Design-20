#ifndef __AST_READ_NODE_H
#define __AST_READ_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"

class ReadNode : public AstNode {
  public:
    ReadNode(const uint32_t line, const uint32_t col
             /* TODO: variable reference */,AstNode *vr);
    ~ReadNode() = default;

    void print() override;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};

	void visitChildNodes(AstNodeVisitor &v){
		if(vr!=NULL) vr->accept(v);
		
	};

  //private:
    // TODO: variable reference
	AstNode *vr=NULL;
};

#endif
