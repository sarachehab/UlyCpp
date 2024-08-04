#include "../../include/control_flow/ast_break.hpp"

void BreakStatement::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    stream << "j " << context.get_end_label() << std::endl;
}

void BreakStatement::Print(std::ostream &stream) const
{
    stream << "break" << std::endl;
}
