#ifndef __AST_FOR_NODE_H
#define __AST_FOR_NODE_H

#include "AST/CompoundStatement.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/assignment.hpp"
#include "AST/ast.hpp"
#include "AST/decl.hpp"

#include <memory>

class SymbolTable;

class ForNode : public AstNode {
  public:
    ForNode(const uint32_t line, const uint32_t col, DeclNode *p_var_decl,
            AssignmentNode *p_initial_statement, ConstantValueNode *p_condition,
            CompoundStatementNode *p_body);
    ~ForNode() = default;

    const ConstantValueNode *getLowerBoundNode() const;
    const ConstantValueNode *getUpperBoundNode() const;

    void setSymbolTable(const SymbolTable *table);
    const SymbolTable *getSymbolTable() const;

    void accept(AstNodeVisitor &p_visitor) override;
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

	void visit_dec_and_assign(AstNodeVisitor &p_visitor){
    		var_decl->accept(p_visitor);
    		initial_statement->accept(p_visitor);
	}

	void visit_constantvalue(AstNodeVisitor &p_visitor){
		condition->accept(p_visitor);
	}

	void visit_body(AstNodeVisitor &p_visitor){
		body->accept(p_visitor);
	}

	const DeclNode *getdecl() const{
		return var_decl.get();
	}

  private:
    std::unique_ptr<DeclNode> var_decl;
    std::unique_ptr<AssignmentNode> initial_statement;
    std::unique_ptr<ConstantValueNode> condition;
    std::unique_ptr<CompoundStatementNode> body;

    const SymbolTable *symbol_table;
};

#endif
