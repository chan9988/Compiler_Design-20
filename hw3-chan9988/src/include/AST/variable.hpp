#ifndef __AST_VARIABLE_NODE_H
#define __AST_VARIABLE_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"

class VariableNode : public AstNode {
  public:
    VariableNode(const uint32_t line, const uint32_t col,char *name,int type,std::vector<int> *arr,int intconstant,double doubleconstant,char *str);
    ~VariableNode() = default;

	void accept(AstNodeVisitor &v){
		v.visit(*this);
	};

	void visitChildNodes(AstNodeVisitor &v){
		if(ch!=NULL) ch->accept(v);
	};

    void print() override;

    void add_child(AstNode *);

  //private:
    // TODO: variable name, type, constant value
	char *name;
	int type;
	std::vector<int> *arr;
	int intconstant; // type=0
	double doubleconstant;  // type=1
	char *str;  // type=2  //type=3 => boolean
	AstNode * ch;
};

#endif
