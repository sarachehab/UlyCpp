#ifndef AST_WHILE_LOOP_HPP
#define AST_WHILE_LOOP_HPP

#include "../ast_node.hpp"
#include "../statements/ast_expression.hpp"
#include "ast_condition_evaluation.hpp"

class WhileLoop : public Node
{
private:
    Node *condition_;
    Node *statement_;

public:
    WhileLoop(Node *condition, Node *statement) : condition_(condition), statement_(statement) {}

    ~WhileLoop()
    {
        delete condition_;
        delete statement_;
    }

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
