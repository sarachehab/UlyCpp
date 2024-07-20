#ifndef CONTEXT_FUNCTIONS
#define CONTEXT_FUNCTIONS

#include <vector>
#include <string>

#include "context_types.hpp"
struct ReturnValue
{
    bool is_pointer = false;
    bool is_array = false;
    Type type;

    ReturnValue() : is_pointer(false), is_array(false), type(Type::_INT) {}
    ReturnValue(bool is_pointer, bool is_array, Type type) : is_pointer(is_pointer), is_array(is_array), type(type){};
};

struct Argument
{
    std::string name;
    bool is_pointer = false;
    bool is_array = false;
    Type type;
    int offset;

    Argument() : name("random"), is_pointer(false), is_array(false), type(Type::_INT), offset(0) {}
    Argument(std::string name, bool is_pointer, bool is_array, Type type, int offset) : name(name), is_pointer(is_pointer), is_array(is_array), type(type), offset(offset){};
};

struct Function
{
    ReturnValue return_value;
    std::vector<Argument> arguments;

    Function() : return_value(ReturnValue()), arguments(std::vector<Argument>{}) {}
    Function(ReturnValue return_value, std::vector<Argument> arguments) : return_value(return_value), arguments(arguments){};
};

#endif
