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

struct Parameter
{
    std::string name;
    bool is_pointer = false;
    bool is_array = false;
    Type type;
    int offset;

    int GetSize() const;

    Parameter() : name("random"), is_pointer(false), is_array(false), type(Type::_INT), offset(0) {}
    Parameter(std::string name, bool is_pointer, bool is_array, Type type, int offset) : name(name), is_pointer(is_pointer), is_array(is_array), type(type), offset(offset){};
};

struct Function
{
    ReturnValue return_value;
    std::vector<Parameter> arguments;

    Function() : return_value(ReturnValue()), arguments(std::vector<Parameter>{}) {}
    Function(ReturnValue return_value, std::vector<Parameter> arguments) : return_value(return_value), arguments(arguments){};
};

#endif
