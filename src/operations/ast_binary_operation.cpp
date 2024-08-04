#include "../../include/operations/ast_binary_operation.hpp"

void BinaryOperation::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    Type type = std::max(context.get_operation_type(), GetType(context));

    context.set_operation_type(type);

    std::string left_register = context.get_register(type);
    left_->EmitRISC(stream, context, left_register);
    context.add_register_to_set(left_register);

    std::string right_register = context.get_register(type);
    right_->EmitRISC(stream, context, right_register);

    stream << GetMneumonic(type) << " " << passed_reg << ", " << left_register << ", " << right_register << std::endl;

    context.deallocate_register(right_register);
    context.deallocate_register(left_register);
    context.remove_register_from_set(left_register);

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
    // Attempt to cast left_ and right_ to Operand
    Operand *leftOperand = dynamic_cast<Operand *>(left_);
    Operand *rightOperand = dynamic_cast<Operand *>(right_);

    // Check if the cast was successful
    if (!leftOperand)
    {
        throw std::runtime_error("Error: dynamic_cast failed for left_ in BinaryOperation::GetType");
    }

    if (!rightOperand)
    {
        throw std::runtime_error("Error: dynamic_cast failed for right_ in BinaryOperation::GetType");
    }

    // Get types from the operands
    Type leftType = leftOperand->GetType(context);
    Type rightType = rightOperand->GetType(context);

    // Return the max type
    return std::max(leftType, rightType);
}
