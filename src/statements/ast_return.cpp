#include "../../include/statements/ast_return.hpp"

void ReturnStatement::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Get return register
    std::string return_register = context.get_return_register();

    // Evaluate expression and store in return register
    if (expression_ != nullptr)
    {
        expression_->EmitRISC(stream, context, return_register);
    }

    // Jump to restore of sp and ra registers
    stream << "j " << context.get_last_function_end_statement() << std::endl;
}

void ReturnStatement::Print(std::ostream &stream) const
{
    stream << "return";
    if (expression_ != nullptr)
    {
        stream << " ";
        expression_->Print(stream);
    }
    stream << ";" << std::endl;
}
