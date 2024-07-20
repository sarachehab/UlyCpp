#include "../../include/primitives/ast_constant.hpp"

void IntConstant::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    stream << "li a0, " << value_ << std::endl;
}

void IntConstant::Print(std::ostream &stream) const
{
    stream << value_;
}
