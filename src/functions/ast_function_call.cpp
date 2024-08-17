#include "../../include/functions/ast_function_call.hpp"

void FunctionCall::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    std::string function_name = dynamic_cast<Identifier *>(identifier_)->GetIdentifier();

    // Push registers for them not to get corrupted
    context.push_registers(stream);

    // Define new function call
    context.set_function_call(function_name);

    // Emit arguments if they exist
    if (argument_list_ != nullptr)
    {
        dynamic_cast<ExpressionList *>(argument_list_)->GetArguments(stream, context, passed_reg);
    }

    // Call function
    context.set_operation_type(GetType(context));
    stream << "call " << function_name << std::endl;

    // Move return value to specified register
    stream << context.move_instruction(context.get_function_call().return_value.type) << " " << passed_reg << ", " << context.get_return_register() << std::endl;

    // Reset to initial state
    context.pop_operation_type();
    context.pop_function_call();
    context.pop_registers(stream);
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

bool FunctionCall::IsPointerOperation(Context &context) const
{
    Function function = context.get_function(dynamic_cast<Identifier *>(identifier_)->GetIdentifier());
    return function.return_value.is_pointer;
}
