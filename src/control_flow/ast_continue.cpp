#include "../../include/control_flow/ast_continue.hpp"

void ContinueStatement::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    stream << "j " << context.get_start_label() << std::endl;
}

void ContinueStatement::Print(std::ostream &stream) const
{
    stream << "continue" << std::endl;
}
