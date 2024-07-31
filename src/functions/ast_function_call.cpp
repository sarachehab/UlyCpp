#include "../../include/functions/ast_function_call.hpp"

void FunctionCall::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    std::string function_name = dynamic_cast<Identifier *>(identifier_)->GetIdentifier();
    context.set_function_call(function_name);

    if (argument_list_ != nullptr)
    {

        dynamic_cast<AssignmentList *>(argument_list_)->GetArguments(stream, context, passed_reg);
    }

    stream << "call " << function_name << std::endl;

    context.pop_function_call();
}

void FunctionCall::Print(std::ostream &stream) const
{
    identifier_->Print(stream);
    stream << "(";
    if (argument_list_ != nullptr)
    {
        argument_list_->Print(stream);
    }
    stream << ")";
}

Type FunctionCall::GetType(Context &context) const
{
    std::string function_name = dynamic_cast<Identifier *>(identifier_)->GetIdentifier();
    Function function = context.get_function(function_name);
    return function.return_value.type;
}
