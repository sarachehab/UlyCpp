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
    SpecifierType type;
    Scope scope;
    int offset;
};

typedef std::unordered_map<std::string, Variable> VariablesLayer;

#endif