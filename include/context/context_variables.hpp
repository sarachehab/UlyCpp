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
 * Contains information on variables, such as whether they are pointers, arrays, their type, and their offset.
 */
struct Variable
{
    bool is_pointer = false;
    bool is_array = false;
    Scope scope;
    Type type;
    int offset;
    int size_array;
    int dereferences_number;

    Variable() : is_pointer(false), is_array(false), scope(Scope::_LOCAL), type(Type::_INT), offset(0), size_array(0), dereferences_number(0) {}
    Variable(bool is_pointer, bool is_array, Type type, int offset, int dereferences_number) : is_pointer(is_pointer), is_array(is_array), scope(Scope::_LOCAL), type(type), offset(offset), size_array(1), dereferences_number(dereferences_number) {}
    Variable(bool is_pointer, bool is_array, int size_array, Type type, int offset, int dereferences_number) : is_pointer(is_pointer), is_array(is_array), scope(Scope::_LOCAL), type(type), offset(offset), size_array(size_array), dereferences_number(dereferences_number) {}
    Variable(bool is_pointer, bool is_array, Type type, Scope scope, int dereferences_number) : is_pointer(is_pointer), is_array(is_array), scope(scope), type(type), offset(0), size_array(1), dereferences_number(dereferences_number) {}
    Variable(bool is_pointer, bool is_array, int size_array, Type type, Scope scope, int dereferences_number) : is_pointer(is_pointer), is_array(is_array), scope(scope), type(type), offset(0), size_array(size_array), dereferences_number(dereferences_number) {}
};

/**
 * @brief Information of variables in a layer
 */
typedef std::unordered_map<std::string, Variable> VariablesLayer;

/**
 * @brief Information of globals
 *
 * Contains information on global variables, such as their type and their offset.
 */
struct Global : public Variable
{
    std::vector<uint32_t> lower_values;
    std::vector<uint32_t> upper_values;
    std::vector<std::string> labels;
    bool with_label = false;

    Global() : Variable() {}
    Global(bool is_pointer, bool is_array, Type type, int dereferences_number) : Variable(is_pointer, is_array, type, Scope::_GLOBAL, dereferences_number) {}
    Global(bool is_pointer, bool is_array, int size_array, Type type, int dereferences_number) : Variable(is_pointer, is_array, size_array, type, Scope::_GLOBAL, dereferences_number) {}

    void print_global(std::ostream &stream) const;

    void print_labels(std::ostream &stream) const;
    void print_numbers(std::ostream &stream) const;

    void push_lower(uint32_t value);

    void push_upper(uint32_t value);

    void push_label(std::string label);
};

#endif
