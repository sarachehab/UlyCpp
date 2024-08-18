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
    Type return_type = IsPointerOperation(context) ? Type::_INT : GetType(context);

    if (return_type != Type::_VOID)
        context.set_operation_type(return_type);

    stream << "call " << function_name << std::endl;

    if (context.evaluating_expression() && !(return_type == Type::_VOID))
    {
        stream << context.move_instruction(return_type) << " " << passed_reg << ", " << context.get_return_register() << std::endl;
    }

    // Reset to initial state
    context.pop_function_call();
    context.pop_registers(stream);

    if (return_type != Type::_VOID)
        context.pop_operation_type();
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
