#ifndef AST_CONTINUE_HPP
#define AST_CONTINUE_HPP

#include "../ast_node.hpp"
#include "ast_flow_breaker.hpp"

class ContinueStatement : public FlowBreaker
{
public:
    ContinueStatement() {}

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
