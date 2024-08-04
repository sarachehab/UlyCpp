#ifndef AST_BREAK_HPP
#define AST_BREAK_HPP

#include "../ast_node.hpp"
#include "ast_flow_breaker.hpp"

class BreakStatement : public FlowBreaker
{
public:
    BreakStatement() {}

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
