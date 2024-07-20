#include "../../include/primitives/ast_constant.hpp"

void IntConstant::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    stream << "li " << passed_reg << ", " << value_ << std::endl;
}

void IntConstant::Print(std::ostream &stream) const
{
    stream << value_;
}
