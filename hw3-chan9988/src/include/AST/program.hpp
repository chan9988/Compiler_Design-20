#ifndef __AST_PROGRAM_NODE_H
#define __AST_PROGRAM_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"

class ProgramNode : public AstNode {
  public:
    ProgramNode(const uint32_t line, const uint32_t col,
                const char *p_name
                /* TODO: return type, declarations, functions,
                 *       compound statement */);
    ~ProgramNode() = default;

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
    const std::string name;
    // TODO: return type, declarations, functions, compound statement
	std::string returntype="void";
	std::vector <AstNode *> ch;
};

#endif
