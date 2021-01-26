#ifndef __AST_CONSTANT_VALUE_NODE_H
#define __AST_CONSTANT_VALUE_NODE_H

#include "AST/expression.hpp"
#include "AST/AstDumper.hpp"

class ConstantValueNode : public ExpressionNode {
  public:
    ConstantValueNode(const uint32_t line, const uint32_t col,int type,int intconstant,double doubleconstant,const char *str);
    ~ConstantValueNode() = default;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};

    void print() override;
    void add_child(AstNode *) {};

  //private:
    // TODO: constant value
    int type;
    int intconstant; // type=0
    double doubleconstant;  // type=1
    const char *str;  // type=2
};

#endif
