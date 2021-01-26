#ifndef __AST_FUNCTION_INVOCATION_NODE_H
#define __AST_FUNCTION_INVOCATION_NODE_H

#include "AST/expression.hpp"
#include "AST/AstDumper.hpp"

class FunctionInvocationNode : public ExpressionNode {
  public:
    FunctionInvocationNode(const uint32_t line, const uint32_t col
                           /* TODO: function name, expressions */,char *name);
    ~FunctionInvocationNode() = default;

    const char *getNameCString() const;

    void print() override;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};

	void visitChildNodes(AstNodeVisitor &v){
		for (auto i: ch){
			i->accept(v);
		}
	};

    void add_child(AstNode *) override;

  //private:
    // TODO: function name, expressions
	char *name;
	std::vector <AstNode *> ch;
	
};

#endif
