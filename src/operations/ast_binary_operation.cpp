#include "../../include/operations/ast_binary_operation.hpp"

void BinaryOperation::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // set type of operation by comparing the type of the operation and the type of the operands
    Type type = std::max(context.get_operation_type(), GetType(context));
    type = IsPointerOperation(context) ? Type::_INT : type;
    context.set_operation_type(type);

    // evaluate left operand
    std::string left_register = context.get_register(type);
    left_->EmitRISC(stream, context, left_register);
    AdjustPointerOperation(stream, context, left_register, left_);

    // add left operand to register set, can be spilled if right part contains function call
    context.add_register_to_set(left_register);

    // evaluate right operand
    std::string right_register = context.get_register(type);
    right_->EmitRISC(stream, context, right_register);
    AdjustPointerOperation(stream, context, right_register, right_);

    // execute desired operation
    stream << GetMneumonic(type) << " " << passed_reg << ", " << left_register << ", " << right_register << std::endl;

    // deallocate registers
    context.deallocate_register(right_register);
    context.deallocate_register(left_register);

    // remove left operand from register set
    context.remove_register_from_set(left_register);

    // set operation type to the type of the operands
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
    Operand *left_operand = dynamic_cast<Operand *>(left_);
    Operand *right_operand = dynamic_cast<Operand *>(right_);

    // Check if the cast was successful
    if (!left_operand)
    {
        throw std::runtime_error("Error: dynamic_cast failed for left_ in BinaryOperation::GetType");
    }

    if (!right_operand)
    {
        throw std::runtime_error("Error: dynamic_cast failed for right_ in BinaryOperation::GetType");
    }

    // Get types from the operands
    Type leftType = left_operand->GetType(context);
    Type rightType = right_operand->GetType(context);

    // Return the max type
    return std::max(leftType, rightType);
}

bool BinaryOperation::IsPointerOperation(Context &context) const
{
    // Attempt to cast left_ and right_ to Operand
    Operand *left_operand = dynamic_cast<Operand *>(left_);
    Operand *right_operand = dynamic_cast<Operand *>(right_);

    // Return true if either operand is a pointer
    return left_operand->IsPointerOperation(context) || right_operand->IsPointerOperation(context);
}

void BinaryOperation::AdjustPointerOperation(std::ostream &stream, Context &context, std::string passed_register, Node *node) const
{
    if (IsPointerOperation(context))
    {
        if (!dynamic_cast<Operand *>(node)->IsPointerOperation(context))
        {
            Type type = GetPointerAjustmentType(context);
            stream << "slli " << passed_register << ", " << passed_register << ", " << types_shift.at(type) << std::endl;
        }
    }
}

Type BinaryOperation::GetPointerAjustmentType(Context &context) const
{

    Operand *left_operand = dynamic_cast<Operand *>(left_);
    Operand *right_operand = dynamic_cast<Operand *>(right_);

    if (left_operand->IsPointerOperation(context))
    {
        return left_operand->GetType(context);
    }
    return right_operand->GetType(context);
}
