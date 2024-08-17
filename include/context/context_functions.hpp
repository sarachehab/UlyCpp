#ifndef CONTEXT_FUNCTIONS
#define CONTEXT_FUNCTIONS

#include <vector>
#include <string>

#include "context_types.hpp"

/**
 * @brief This struct represents the return value of a function.
 *
 * It saves the type of the return value, if it is a pointer and if it is an array.
 */
struct ReturnValue
{
    bool is_pointer = false;
    bool is_array = false;
    Type type;
    int dereference_number;

    ReturnValue() : is_pointer(false), is_array(false), type(Type::_INT), dereference_number(0) {}
    ReturnValue(bool is_pointer, bool is_array, Type type, int dereference_number) : is_pointer(is_pointer), is_array(is_array), type(type), dereference_number(dereference_number) {};
};

/**
 * @brief This struct represents a parameter of a function.
 *
 * It saves the name of the parameter, if it is a pointer, if it is an array, the type of the parameter and the offset in the stack.
 */
struct Parameter
{
    std::string name;
    bool is_pointer = false;
    bool is_array = false;
    Type type;
    int offset;
    int dereference_number;

    /**
     * @brief This function returns the size of the parameter.
     *
     * @return The size of the parameter.
     */
    int GetSize() const;

    Parameter() : name("random"), is_pointer(false), is_array(false), type(Type::_INT), offset(0), dereference_number(0) {}
    Parameter(std::string name, bool is_pointer, bool is_array, Type type, int offset, int dereference_number) : name(name), is_pointer(is_pointer), is_array(is_array), type(type), offset(offset), dereference_number(dereference_number) {};
};

/**
 * @brief This struct represents a function.
 *
 * It saves the return value of the function and the arguments of the function.
 * It also keeps tracks of stack offsets and types.
 */
struct Function
{
    ReturnValue return_value;
    std::vector<Parameter> arguments;

    Function() : return_value(ReturnValue()), arguments(std::vector<Parameter>{}) {}
    Function(ReturnValue return_value, std::vector<Parameter> arguments) : return_value(return_value), arguments(arguments) {};
};

#endif
