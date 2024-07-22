#include "../../include/operations/ast_logical_operation.hpp"

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

std::string LogicalAnd::GetOperation() const { return " & "; }

std::string LogicalOr::GetMneumonic(Type type) const { return "or"; }

std::string LogicalOr::GetOperation() const { return " | "; }
