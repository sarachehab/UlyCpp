#include "../../include/operations/ast_binary_operation.hpp"

void BinaryOperation::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    Type type = std::max(context.get_operation_type(), GetType(context));

    context.set_operation_type(type);

    std::string left_register = context.get_register(type);
    std::string right_register = context.get_register(type);

    left_->EmitRISC(stream, context, left_register);
    right_->EmitRISC(stream, context, right_register);
    stream << GetMneumonic(type) << " " << passed_reg << ", " << left_register << ", " << right_register << std::endl;

    context.deallocate_register(right_register);
    context.deallocate_register(left_register);

    context.pop_operation_type();
}

void BinaryOperation::Print(std::ostream &stream) const
{
    left_->Print(stream);
    stream << GetOperation();
    right_->Print(stream);
}

Type BinaryOperation::GetType(Context &context) const
{
    Type leftType = dynamic_cast<Operand *>(left_)->GetType(context);
    Type rightType = dynamic_cast<Operand *>(right_)->GetType(context);

    return std::max(leftType, rightType);
}
