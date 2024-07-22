#include "../../include/context/context.hpp"

const std::unordered_map<Type, int> Context::types_size = {
    {Type::_VOID, 0},
    {Type::_CHAR, 1},
    {Type::_SHORT, 2},
    {Type::_UNSIGNED_INT, 4},
    {Type::_INT, 4},
    {Type::_LONG, 8},
    {Type::_FLOAT, 4},
    {Type::_DOUBLE, 8},
};

const std::unordered_map<Type, std::string> Context::assembler_directives = {
    {Type::_VOID, ".space"},
    {Type::_CHAR, ".byte"},
    {Type::_SHORT, ".half"},
    {Type::_UNSIGNED_INT, ".word"},
    {Type::_INT, ".word"},
    {Type::_LONG, ".word"},
    {Type::_FLOAT, ".word"},
    {Type::_DOUBLE, ".word"},
};

void Context::set_operation_type(Type type) { operation_type_stack.push(type); }

void Context::pop_operation_type() { operation_type_stack.pop(); }

Type Context::get_operation_type() const { return operation_type_stack.top(); }
