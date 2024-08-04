#ifndef CONTROL_FLOW_HPP
#define CONTROL_FLOW_HPP

#include "../ast_node.hpp"

/**
 * @brief Abstract class for control
 *
 * Represents a control flow, such as an IF, ELSE, WHILE, DO_WHILE, FOR
 */
class ControlFlow : public Node
{
public:
    using Node::Node;
    virtual ~ControlFlow() = default;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override = 0;
    void Print(std::ostream &stream) const override = 0;
};

#endif
