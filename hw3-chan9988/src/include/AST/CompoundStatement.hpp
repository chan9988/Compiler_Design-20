#ifndef __AST_COMPOUND_STATEMENT_NODE_H
#define __AST_COMPOUND_STATEMENT_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"

class CompoundStatementNode : public AstNode {
  public:
    CompoundStatementNode(const uint32_t line, const uint32_t col
                          /* TODO: declarations, statements */);
    ~CompoundStatementNode() = default;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};

	void visitChildNodes(AstNodeVisitor &v){
		for (auto i: decl){
			i->accept(v);
		}
		for (auto i: stat){
			i->accept(v);
		}
	};

    void print() override;
	void add_de(AstNode *);
	void add_st(AstNode *);

  //private:
    // TODO: declarations, statements
	std::vector<AstNode *> decl;
	std::vector<AstNode *> stat;
};

#endif
