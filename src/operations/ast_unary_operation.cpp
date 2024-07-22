#include "../../include/operations/ast_unary_operation.hpp"

void UnaryOperation::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    Type type = std::max(context.get_operation_type(), GetType(context));

    context.set_operation_type(type);

    std::string left_register = context.get_register(type);

    expression_->EmitRISC(stream, context, left_register);
    stream << GetMneumonic(type) << " " << passed_reg << ", " << left_register << std::endl;

    context.deallocate_register(left_register);

    context.pop_operation_type();
}

void UnaryOperation::Print(std::ostream &stream) const
{
    stream << GetOperation();
    expression_->Print(stream);
}

Type UnaryOperation::GetType(Context &context) const
{
    return dynamic_cast<Operand *>(expression_)->GetType(context);
}
