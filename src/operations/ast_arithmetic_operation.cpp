#include "../../include/operations/ast_arithmetic_operation.hpp"

std::string Addition::GetMneumonic(Type type) const
{
    switch (type)
    {
    case Type::_INT:
        return "add";
    case Type::_UNSIGNED_INT:
        return "add";
    case Type::_CHAR:
        return "add";
    case Type::_SHORT:
        return "add";
    case Type::_LONG:
        return "add";
    case Type::_FLOAT:
        return "fadd.s";
    case Type::_DOUBLE:
        return "fadd.d";
    default:
        throw std::runtime_error("Addition::GetMneumonic: Type not supported");
    }
}

std::string Addition::GetOperation() const { return " + "; }

std::string Substraction::GetMneumonic(Type type) const
{
    switch (type)
    {
    case Type::_INT:
        return "sub";
    case Type::_UNSIGNED_INT:
        return "sub";
    case Type::_CHAR:
        return "sub";
    case Type::_SHORT:
        return "sub";
    case Type::_LONG:
        return "sub";
    case Type::_FLOAT:
        return "fsub.s";
    case Type::_DOUBLE:
        return "fsub.d";
    default:
        throw std::runtime_error("Substraction::GetMneumonic: Type not supported");
    }
}

std::string Substraction::GetOperation() const { return " - "; }

std::string Multiplication::GetMneumonic(Type type) const
{
    switch (type)
    {
    case Type::_INT:
        return "mul";
    case Type::_UNSIGNED_INT:
        return "mul";
    case Type::_CHAR:
        return "mul";
    case Type::_SHORT:
        return "mul";
    case Type::_LONG:
        return "mul";
    case Type::_FLOAT:
        return "fmul.s";
    case Type::_DOUBLE:
        return "fmul.d";
    default:
        throw std::runtime_error("Multiplication::GetMneumonic: Type not supported");
    }
}

std::string Multiplication::GetOperation() const { return " * "; }

std::string Division::GetMneumonic(Type type) const
{
    switch (type)
    {
    case Type::_INT:
        return "div";
    case Type::_UNSIGNED_INT:
        return "div";
    case Type::_CHAR:
        return "div";
    case Type::_SHORT:
        return "div";
    case Type::_LONG:
        return "div";
    case Type::_FLOAT:
        return "fdiv.s";
    case Type::_DOUBLE:
        return "fdiv.d";
    default:
        throw std::runtime_error("Division::GetMneumonic: Type not supported");
    }
}

std::string Division::GetOperation() const { return " / "; }

std::string Modulus::GetMneumonic(Type type) const
{
    switch (type)
    {
    case Type::_INT:
        return "rem";
    case Type::_UNSIGNED_INT:
        return "remu";
    case Type::_CHAR:
        return "rem";
    case Type::_SHORT:
        return "rem";
    case Type::_LONG:
        return "rem";
    case Type::_FLOAT:
        return "rem";
    case Type::_DOUBLE:
        return "rem";
    default:
        throw std::runtime_error("Modulus::GetMneumonic: Type not supported");
    }
}

std::string Modulus::GetOperation() const { return " % "; }
