#include "../../include/context/context.hpp"

std::string Context::store_instruction(SpecifierType type) const
{
    switch (type)
    {
    case SpecifierType::_CHAR:
        return "sb";
    case SpecifierType::_SHORT:
        return "sh";
    case SpecifierType::_INT:
    case SpecifierType::_UNSIGNED_INT:
    case SpecifierType::_LONG:
        return "sw";
    case SpecifierType::_FLOAT:
        return "fsw";
    case SpecifierType::_DOUBLE:
        return "fsd";
    case SpecifierType::_VOID:
        throw std::runtime_error("Context::store_instruction: VOID not supported");
    default:
        throw std::runtime_error("Context::store_instruction: Invalid store type");
    }
}

std::string Context::load_instruction(SpecifierType type) const
{
    switch (type)
    {
    case SpecifierType::_CHAR:
        return "lb";
    case SpecifierType::_SHORT:
        return "lh";
    case SpecifierType::_INT:
    case SpecifierType::_UNSIGNED_INT:
    case SpecifierType::_LONG:
        return "lw";
    case SpecifierType::_FLOAT:
        return "flw";
    case SpecifierType::_DOUBLE:
        return "fld";
    case SpecifierType::_VOID:
        throw std::runtime_error("Context::load_instruction: VOID not supported");
    default:
        throw std::runtime_error("Context::load_instruction: Invalid store type");
    }
}

std::string Context::move_instruction(SpecifierType type) const
{
    switch (type)
    {
    case SpecifierType::_CHAR:
    case SpecifierType::_SHORT:
    case SpecifierType::_INT:
    case SpecifierType::_UNSIGNED_INT:
    case SpecifierType::_LONG:
        return "mv";
    case SpecifierType::_FLOAT:
        return "fmv.s";
    case SpecifierType::_DOUBLE:
        return "fmv.d";
    case SpecifierType::_VOID:
        throw std::runtime_error("Context::move_instruction: VOID not supported");
    default:
        throw std::runtime_error("Context::move_instruction: Invalid store type");
    }
}