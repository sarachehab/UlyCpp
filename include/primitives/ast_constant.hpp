#ifndef AST_CONSTANT_HPP
#define AST_CONSTANT_HPP

#include "../ast_node.hpp"
#include "../operations/ast_operand.hpp"

class IntConstant : public Operand
{
private:
    int value_;

public:
    IntConstant(int value) : value_(value) {}

    Type GetType(Context &context) const override;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
