#ifndef AST_RETURN_HPP
#define AST_RETURN_HPP

#include "../ast_node.hpp"
#include "../control_flow/ast_flow_breaker.hpp"

class ReturnStatement : public FlowBreaker
{
private:
    Node *expression_;

public:
    ReturnStatement(Node *expression) : expression_(expression) {}
    ~ReturnStatement()
    {
        delete expression_;
    };

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
