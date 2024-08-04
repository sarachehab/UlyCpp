#ifndef CONTROL_FLOW_HPP
#define CONTROL_FLOW_HPP

#include "../ast_node.hpp"

class ControlFlow : public Node
{
public:
    using Node::Node;
    virtual ~ControlFlow() = default;

    virtual int GetScopeOffset(Context &context) const = 0;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override = 0;
    void Print(std::ostream &stream) const override = 0;
};

#endif
