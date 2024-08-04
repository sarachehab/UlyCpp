#ifndef AST_CONDITIONAL_STATEMENT_HPP
#define AST_CONDITIONAL_STATEMENT_HPP

#include "../ast_node.hpp"
#include "ast_condition_evaluation.hpp"
#include "ast_control_flow.hpp"

class IfElse : public ControlFlow
{
private:
    Node *condition_;
    Node *true_statement_;
    Node *false_statement_;

public:
    IfElse(Node *condition, Node *true_statement) : condition_(condition), true_statement_(true_statement), false_statement_(nullptr) {}
    IfElse(Node *condition, Node *true_statement, Node *false_statement) : condition_(condition), true_statement_(true_statement), false_statement_(false_statement) {}

    ~IfElse()
    {
        delete condition_;
        delete true_statement_;
        delete false_statement_;
    }

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
