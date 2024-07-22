#include "../../include/operations/ast_comparaison_strict.hpp"

void StrictComparaisonOperation::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Determine type of operands
    Type right_type = dynamic_cast<Operand *>(right_)->GetType(context);
    Type left_type = dynamic_cast<Operand *>(left_)->GetType(context);
    Type type = std::max(right_type, left_type);

    context.set_operation_type(type);

    std::string left_register = context.get_register(type);
    std::string right_register = context.get_register(type);

    left_->EmitRISC(stream, context, left_register);
    right_->EmitRISC(stream, context, right_register);

    stream << GetMneumonic(type) << " " << passed_reg << ", " << left_register << ", " << right_register << std::endl;

    context.deallocate_register(left_register);
    context.deallocate_register(right_register);

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
    case Type::_LONG:
        return "flt.d";
    default:
        throw std::runtime_error("LessThan::GetMneumonic - Invalid type for LessThan operation");
    }
}

std::string LessThan::GetOperation() const { return " < "; }

std::string GreaterThan::GetMneumonic(Type type) const
{
    switch (type)
    {
    case Type::_CHAR:
        return "sgt";
    case Type::_SHORT:
        return "sgt";
    case Type::_INT:
        return "sgt";
    case Type::_UNSIGNED_INT:
        return "sgtu";
    case Type::_FLOAT:
        return "fgt.s";
    case Type::_LONG:
        return "fgt.d";
    default:
        throw std::runtime_error("LessThan::GetMneumonic - Invalid type for LessThan operation");
    }
}

std::string GreaterThan::GetOperation() const { return " > "; }
