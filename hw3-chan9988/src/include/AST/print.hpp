#ifndef __AST_PRINT_NODE_H
#define __AST_PRINT_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"

class PrintNode : public AstNode {
  public:
    PrintNode(const uint32_t line, const uint32_t col
              /* TODO: expression */,AstNode *ch);
    ~PrintNode() = default;

    void print() override;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};

	void visitChildNodes(AstNodeVisitor &v){
		if(ch!=NULL) ch->accept(v);
	};

  //private:
    // TODO: expression
	AstNode *ch;
};

#endif
