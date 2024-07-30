#include "../../include/operations/ast_comparaison_equality_check.hpp"

void EqualityCheck::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Determine type of operands
    Type right_type = dynamic_cast<Operand *>(right_)->GetType(context);
    Type left_type = dynamic_cast<Operand *>(left_)->GetType(context);
    Type type = std::max(right_type, left_type);

    context.set_operation_type(type);

    std::string right_register = context.get_register(type);
    std::string left_register = context.get_register(type);

    right_->EmitRISC(stream, context, right_register);
    left_->EmitRISC(stream, context, left_register);

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

    context.pop_operation_type();
}

std::string EqualityCheck::GetOperation() const { return " == "; }
