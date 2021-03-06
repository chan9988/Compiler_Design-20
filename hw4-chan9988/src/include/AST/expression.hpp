#ifndef __AST_EXPRESSION_NODE_H
#define __AST_EXPRESSION_NODE_H

#include "AST/PType.hpp"
#include "AST/ast.hpp"
#include "AST/constant.hpp"

class ExpressionNode : public AstNode {
  public:
    ExpressionNode(const uint32_t line, const uint32_t col);
    ~ExpressionNode() = default;


  //protected:
    // for carrying type of result of an expression
    PTypeSharedPtr type = nullptr;
	const std::string name;
	int dim=0;
	char t[50]="\0";
};

#endif
