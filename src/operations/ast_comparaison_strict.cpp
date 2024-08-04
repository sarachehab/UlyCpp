#include "../../include/operations/ast_comparaison_strict.hpp"

void StrictComparaisonOperation::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Determine type of operands
    Type right_type = dynamic_cast<Operand *>(right_)->GetType(context);
    Type left_type = dynamic_cast<Operand *>(left_)->GetType(context);

    // Determine type for Mneumonic
    Type type = std::max(right_type, left_type);

    context.set_operation_type(type);

    // Evaluate left operand
    std::string left_register = context.get_register(type);
    left_->EmitRISC(stream, context, left_register);

    // Add left operand to register set, can be spilled if right operand contains function call
    context.add_register_to_set(left_register);

    // Evaluate right operand
    std::string right_register = context.get_register(type);
    right_->EmitRISC(stream, context, right_register);

    // Execute operation
    stream << GetMneumonic(type) << " " << passed_reg << ", " << left_register << ", " << right_register << std::endl;

    // deallocate registers
    context.deallocate_register(left_register);
    context.deallocate_register(right_register);

    // remove left operand from register set
    context.remove_register_from_set(left_register);

    // pop operation type from stack
    context.pop_operation_type();
}

std::string LessThan::GetMneumonic(Type type) const
{
    switch (type)
    {
    case Type::_CHAR:
        return "slt";
    case Type::_SHORT:
        return "slt";
    case Type::_INT:
        return "slt";
    case Type::_UNSIGNED_INT:
        return "sltu";
    case Type::_FLOAT:
        return "flt.s";
    case Type::_DOUBLE:
        return "flt.d";
    default:
        throw std::runtime_error("LessThan::GetMneumonic - Invalid type for LessThan operation");
    }
}

std::string LessThan::GetOperation() const { return " < "; }
