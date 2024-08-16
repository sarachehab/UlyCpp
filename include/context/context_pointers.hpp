#ifndef CONTEXT_POINTERS_HPP
#define CONTEXT_POINTERS_HPP

#include "context_types.hpp"

struct Pointer
{
    Type underlying_type;
    int number_dereferences;

    Pointer() : underlying_type(Type::_VOID), number_dereferences(0) {}
    Pointer(Type underlying_type, int number_dereferences) : underlying_type(underlying_type), number_dereferences(number_dereferences) {}
};

#endif
