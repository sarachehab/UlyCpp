#ifndef CONTEXT_VARIABLES
#define CONTEXT_VARIABLES

#include "context_types.hpp"

/**
 * @brief Enum class for scopes
 *
 * Precises if declaration is Global or Local
 */
enum class Scope
{
    _GLOBAL,
    _LOCAL,
};

/**
 * @brief Information on variables
 *
 * Contains information on variables, such as whether they are pointers, arrays, their type, their scope, and their offset.
 */
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
