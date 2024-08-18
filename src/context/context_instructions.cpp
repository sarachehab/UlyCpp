#include "../../include/context/context.hpp"

std::string Context::store_instruction(Type type) const
{
    switch (type)
    {
    case Type::_CHAR:
        return "sb";
    case Type::_SHORT:
        return "sh";
    case Type::_INT:
    case Type::_UNSIGNED_INT:
    case Type::_LONG:
        return "sw";
    case Type::_FLOAT:
        return "fsw";
    case Type::_DOUBLE:
        return "fsd";
    case Type::_VOID:
        throw std::runtime_error("Context::store_instruction: VOID not supported");
    default:
        throw std::runtime_error("Context::store_instruction: Invalid store type");
    }
}

std::string Context::load_instruction(Type type) const
{
    switch (type)
    {
    case Type::_CHAR:
        return "lbu";
    case Type::_SHORT:
        return "lh";
    case Type::_INT:
    case Type::_UNSIGNED_INT:
    case Type::_LONG:
        return "lw";
    case Type::_FLOAT:
        return "flw";
    case Type::_DOUBLE:
        return "fld";
    case Type::_VOID:
        throw std::runtime_error("Context::load_instruction: VOID not supported");
    default:
        throw std::runtime_error("Context::load_instruction: Invalid store type");
    }
}

std::string Context::move_instruction(Type type) const
{
    switch (type)
    {
    case Type::_CHAR:
    case Type::_SHORT:
    case Type::_INT:
    case Type::_UNSIGNED_INT:
    case Type::_LONG:
        return "mv";
    case Type::_FLOAT:
        return "fmv.s";
    case Type::_DOUBLE:
        return "fmv.d";
    case Type::_VOID:
        throw std::runtime_error("Context::move_instruction: VOID not supported");
    default:
        throw std::runtime_error("Context::move_instruction: Invalid store type");
    }
}
