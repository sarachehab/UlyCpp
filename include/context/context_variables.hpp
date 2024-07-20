#ifndef CONTEXT_VARIABLES
#define CONTEXT_VARIABLES

#include "context_types.hpp"

enum class Scope
{
    _GLOBAL,
    _LOCAL,
};

struct Variable
{
    bool is_pointer = false;
    bool is_array = false;
    Type type;
    Scope scope;
    int offset;

    Variable() : is_pointer(false), is_array(false), type(Type::_INT), scope(Scope::_LOCAL), offset(0) {}
    Variable(bool is_pointer, bool is_array, Type type, Scope scope, int offset) : is_pointer(is_pointer), is_array(is_array), type(type), scope(scope), offset(offset) {}
};

typedef std::unordered_map<std::string, Variable> VariablesLayer;

#endif
