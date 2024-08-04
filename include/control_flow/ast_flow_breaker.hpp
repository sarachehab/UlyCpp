#ifndef AST_FLOW_BREAKER_HPP
#define AST_FLOW_BREAKER_HPP

#include "ast_node.hpp"

class FlowBreaker : public Node
{
public:
    FlowBreaker() {}

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override = 0;
    void Print(std::ostream &stream) const override = 0;
};

#endif
