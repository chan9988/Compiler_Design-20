#ifndef __AST_H
#define __AST_H

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

extern int tab;

class AstNodeVisitor;

struct Location {
    Location(const uint32_t line, const uint32_t col) : line(line), col(col) {}

    uint32_t line;
    uint32_t col;
};

class AstNode {
  public:
    AstNode(const uint32_t line, const uint32_t col);
    virtual ~AstNode() = 0;

    const Location &getLocation() const;
    virtual void print() = 0;
    virtual void add_child(AstNode *){};
	virtual void visitChildNodes(AstNodeVisitor &){};
	virtual void accept(AstNodeVisitor &){};
	virtual void add_de(AstNode *){};
	virtual void add_arg(int){};
	virtual void add_compoundstatement(AstNode *){};
	virtual void add_st(AstNode *){};
  protected:
    const Location location;
};

#endif
