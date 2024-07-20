#ifndef CONTEXT_FUNCTIONS
#define CONTEXT_FUNCTIONS

#include <vector>
#include <string>

#include "context_types.hpp"

struct ReturnValue
{
    bool is_pointer = false;
    bool is_array = false;
    SpecifierType type;
};

struct Argument
{
    std::string name;
    bool is_pointer = false;
    bool is_array = false;
    SpecifierType type;
    int offset;
};

struct Function
{
    ReturnValue return_value;
    std::vector<Argument> arguments;
};

#endif