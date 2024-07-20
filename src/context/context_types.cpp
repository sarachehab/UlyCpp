#include "../../include/context/context.hpp"

const std::unordered_map<SpecifierType, int> Context::types_size = {
    {SpecifierType::_VOID, 0},
    {SpecifierType::_CHAR, 1},
    {SpecifierType::_SHORT, 2},
    {SpecifierType::_UNSIGNED_INT, 4},
    {SpecifierType::_INT, 4},
    {SpecifierType::_LONG, 8},
    {SpecifierType::_FLOAT, 4},
    {SpecifierType::_DOUBLE, 8},
};

const std::unordered_map<SpecifierType, std::string> Context::assembler_directives = {
    {SpecifierType::_VOID, ".space"},
    {SpecifierType::_CHAR, ".byte"},
    {SpecifierType::_SHORT, ".half"},
    {SpecifierType::_UNSIGNED_INT, ".word"},
    {SpecifierType::_INT, ".word"},
    {SpecifierType::_LONG, ".word"},
    {SpecifierType::_FLOAT, ".word"},
    {SpecifierType::_DOUBLE, ".word"},
};