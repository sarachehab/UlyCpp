#ifndef ast_operand_HPP
#define ast_operand_HPP

#include "../ast_node.hpp"

class Operand : public Node
{
public:
    Operand() {}
    ~Operand() {}

    virtual Type GetType(Context &context) const = 0;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override = 0;
    void Print(std::ostream &stream) const override = 0;
};

#endif
