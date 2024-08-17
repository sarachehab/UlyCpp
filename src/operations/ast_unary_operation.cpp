#include "../../include/operations/ast_unary_operation.hpp"

void UnaryOperation::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Get the type of the operation
    Type type = std::max(context.get_operation_type(), GetType(context));
    context.set_operation_type(type);

    // Evaluate the expression
    std::string operation_reg = context.get_register(type);
    expression_->EmitRISC(stream, context, operation_reg);

    // Execute the desired operation
    stream << GetMneumonic(type) << " " << passed_reg << ", " << operation_reg << std::endl;

    // Deallocate the register
    context.deallocate_register(operation_reg);

    context.pop_operation_type();
}

void UnaryOperation::Print(std::ostream &stream) const
{
    stream << GetOperation();
    stream << "(";
    expression_->Print(stream);
    stream << ")";
}

Type UnaryOperation::GetType(Context &context) const
{
    return dynamic_cast<Operand *>(expression_)->GetType(context);
}

bool UnaryOperation::IsPointerOperation(Context &context) const
{
    return dynamic_cast<Operand *>(expression_)->IsPointerOperation(context);
}
