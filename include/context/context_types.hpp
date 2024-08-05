#ifndef CONTEXT_TYPES
#define CONTEXT_TYPES

#include <unordered_map>
#include <string>

/**
 * @brief Enum class for types
 */
enum class Type
{
    _VOID,
    _CHAR,
    _SHORT,
    _UNSIGNED_INT,
    _INT,
    _LONG,
    _FLOAT,
    _DOUBLE,
};

/**
 * @brief Map of types to their size in bytes
 *
 * Used in conjunction with Context::increase_stack_size.
 * Used with SizeOf operator.
 */
const std::unordered_map<Type, int> types_size = {
    {Type::_VOID, 0},
    {Type::_CHAR, 1},
    {Type::_SHORT, 2},
    {Type::_UNSIGNED_INT, 4},
    {Type::_INT, 4},
    {Type::_LONG, 8},
    {Type::_FLOAT, 4},
    {Type::_DOUBLE, 8},
};

/**
 * @brief Map of types to their log2(size)
 *
 * Used in conjunction with Context::increase_stack_size.
 * Used with SizeOf operator.
 */
const std::unordered_map<Type, int> types_shift = {
    {Type::_VOID, 0},
    {Type::_CHAR, 0},
    {Type::_SHORT, 1},
    {Type::_UNSIGNED_INT, 2},
    {Type::_INT, 2},
    {Type::_LONG, 3},
    {Type::_FLOAT, 2},
    {Type::_DOUBLE, 3},
};

/**
 * @brief Map of types to their assembler directives
 */
const std::unordered_map<Type, std::string> assembler_directives = {
    {Type::_VOID, ".space"},
    {Type::_CHAR, ".byte"},
    {Type::_SHORT, ".half"},
    {Type::_UNSIGNED_INT, ".word"},
    {Type::_INT, ".word"},
    {Type::_LONG, ".word"},
    {Type::_FLOAT, ".word"},
    {Type::_DOUBLE, ".word"},
};

#endif
