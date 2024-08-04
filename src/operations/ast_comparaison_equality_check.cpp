#include "../../include/operations/ast_comparaison_equality_check.hpp"

void EqualityCheck::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Determine type of operands
    Type right_type = dynamic_cast<Operand *>(right_)->GetType(context);
    Type left_type = dynamic_cast<Operand *>(left_)->GetType(context);

    // Determine type for Mneumonic
    Type type = std::max(right_type, left_type);

    // Set operation type
    context.set_operation_type(type);

    // Evaluate left operand
    std::string left_register = context.get_register(type);
    left_->EmitRISC(stream, context, left_register);

    // Add left operand to register set, can be spilled if right operand contains function call
    context.add_register_to_set(left_register);

    // Evaluate right operand
    std::string right_register = context.get_register(type);
    right_->EmitRISC(stream, context, right_register);

    // Check equality
    switch (type)
    {
    case Type::_CHAR:
    case Type::_SHORT:
    case Type::_INT:
    case Type::_UNSIGNED_INT:
        stream << "sub " << passed_reg << ", " << left_register << ", " << right_register << std::endl;
        stream << "seqz " << passed_reg << ", " << passed_reg << std::endl;
        break;
    case Type::_FLOAT:
        stream << "feq.s " << passed_reg << ", " << left_register << ", " << right_register << std::endl;
        stream << "snez " << passed_reg << ", " << passed_reg << std::endl;
        break;
    case Type::_DOUBLE:
        stream << "feq.d " << passed_reg << ", " << left_register << ", " << right_register << std::endl;
        stream << "snez " << passed_reg << ", " << passed_reg << std::endl;
        break;
    default:
        throw std::runtime_error("EqualityCheck::EmitRISC: Floating point equality check not supported");
    }

    // Deallocate registers
    context.deallocate_register(left_register);
    context.deallocate_register(right_register);

    // Pop operation type from stack
    context.pop_operation_type();

    // Remove left operand from register set
    context.remove_register_from_set(left_register);
}

std::string EqualityCheck::GetOperation() const { return " == "; }
