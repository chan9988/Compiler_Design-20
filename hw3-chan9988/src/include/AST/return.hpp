#ifndef __AST_RETURN_NODE_H
#define __AST_RETURN_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"

class ReturnNode : public AstNode {
  public:
    ReturnNode(const uint32_t line, const uint32_t col
               /* TODO: expression */,AstNode *ex);
    ~ReturnNode() = default;

    void print() override;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};

	void visitChildNodes(AstNodeVisitor &v){
		if(ex!=NULL) ex->accept(v);
	};

  //private:
    // TODO: expression
	AstNode *ex=NULL;
};

#endif
