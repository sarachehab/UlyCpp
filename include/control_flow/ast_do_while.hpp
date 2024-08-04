#ifndef AST_DO_WHILE_HPP
#define AST_DO_WHILE_HPP

#include "../ast_node.hpp"
#include "ast_control_flow.hpp"
#include "ast_condition_evaluation.hpp"

class DoWhileLoop : public ControlFlow
{
private:
    Node *body_;
    Node *condition_;

public:
    DoWhileLoop(Node *body, Node *condition) : body_(body), condition_(condition) {}
    ~DoWhileLoop()
    {
        delete body_;
        delete condition_;
    }

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
