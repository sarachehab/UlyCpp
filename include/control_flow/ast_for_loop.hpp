#ifndef AST_FOR_LOOP_HPP
#define AST_FOR_LOOP_HPP

#include "../ast_node.hpp"
#include "ast_control_flow.hpp"
#include "ast_condition_evaluation.hpp"

class ForLoop : public ControlFlow
{
private:
    Node *initialization_;
    Node *condition_;
    Node *iteration_;
    Node *body_;

public:
    ForLoop(Node *initialization, Node *condition, Node *body) : initialization_(initialization), condition_(condition), iteration_(nullptr), body_(body) {}
    ForLoop(Node *initialization, Node *condition, Node *iteration, Node *body) : initialization_(initialization), condition_(condition), iteration_(iteration), body_(body) {}

    ~ForLoop()
    {
        delete initialization_;
        delete condition_;
        delete iteration_;
        delete body_;
    }

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
