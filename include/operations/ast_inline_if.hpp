#ifndef AST_INLINE_IF_HPP
#define AST_INLINE_IF_HPP

#include "../ast_node.hpp"
#include "ast_operand.hpp"
#include "../control_flow/ast_if_else.hpp"

class InlineIf : public Operand
{
protected:
    Node *condition_;
    Node *true_statement_;
    Node *false_statement_;
    IfElse *if_else_;

public:
    InlineIf(Node *condition, Node *true_statement, Node *false_statement) : condition_(condition), true_statement_(true_statement), false_statement_(false_statement)
    {
        if_else_ = new IfElse(condition, true_statement, false_statement);
    };

    ~InlineIf()
    {
        delete if_else_;
    };

    Type GetType(Context &context) const override;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
