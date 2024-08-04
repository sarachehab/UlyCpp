#include "../../include/operations/ast_logical_operation.hpp"

void LogicalOperation::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Get the type of the operation
    Type type = std::max(context.get_operation_type(), GetType(context));
    context.set_operation_type(type);

    // Evaluate left operand
    std::string left_register = context.get_register(type);
    left_->EmitRISC(stream, context, left_register);

    // Add left operand to register set, can be spilled if right operand contains function call
    context.add_register_to_set(left_register);

    // Evaluate right operand
    std::string right_register = context.get_register(type);
    right_->EmitRISC(stream, context, right_register);

    // Evaluate temporary register to check boolean value
    std::string tmp_register = context.get_register(Type::_INT);
    stream << "snez " << tmp_register << ", " << left_register << std::endl;
    stream << "snez " << passed_reg << ", " << right_register << std::endl;

    // Execute desired operation
    stream << GetMneumonic(type) << " " << passed_reg << ", " << tmp_register << ", " << passed_reg << std::endl;

    // Deallocate registers
    context.deallocate_register(right_register);
    context.deallocate_register(left_register);
    context.deallocate_register(tmp_register);

    // Remove left operand from register set
    context.remove_register_from_set(left_register);

    context.pop_operation_type();
}

std::string Negate::GetMneumonic(Type type) const
{
    switch (type)
    {
    case Type::_CHAR:
        return "neg";
    case Type::_SHORT:
        return "neg";
    case Type::_INT:
        return "neg";
    case Type::_UNSIGNED_INT:
        return "neg";
    case Type::_LONG:
        return "fneg.s";
    case Type::_FLOAT:
        return "fneg.s";
    default:
        throw std::runtime_error("Negate::GetMneumonic - Invalid type");
    }
}

std::string Negate::GetOperation() const { return " - "; }

std::string LogicalAnd::GetMneumonic(Type type) const { return "and"; }

std::string LogicalAnd::GetOperation() const { return " && "; }

std::string LogicalOr::GetMneumonic(Type type) const { return "or"; }

std::string LogicalOr::GetOperation() const { return " || "; }

std::string Inverse::GetMneumonic(Type type) const { return "seqz"; }

std::string Inverse::GetOperation() const { return "! "; }
