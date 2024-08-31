#include "../../include/context/context.hpp"

bool Context::is_typedef(std::string label)
{
    // Iterate through variable bindings in reverse order, from child scope to parent scope
    for (auto it = custom_typedef.rbegin(); it != custom_typedef.rend(); ++it)
    {
        if (it->find(label) != it->end())
        {
            return true;
        }
    }

    return false;
}

TypedefSpec Context::get_typedef_spec(std::string label)
{
    // Iterate through variable bindings in reverse order, from child scope to parent scope
    for (auto it = custom_typedef.rbegin(); it != custom_typedef.rend(); ++it)
    {
        if (it->find(label) != it->end())
        {
            return it->at(label);
        }
    }

    throw std::runtime_error("Context::get_typedef_specs - no corresponding spec found");
}

int Context::get_typedef_base_pointers(std::string alias)
{
    TypedefSpec typedef_spec = get_typedef_spec(alias);
    return typedef_spec.number_pointers_;
}

Type Context::get_typedef_base_type(std::string alias)
{
    TypedefSpec typedef_spec = get_typedef_spec(alias);
    return typedef_spec.type_;
}

void Context::define_typedef(std::string label, TypedefSpec typedef_spec)
{
    if (label.empty())
    {
        throw std::runtime_error("Context::define_typedef: Attempted to define a typedef with an empty label");
    }

    if (custom_typedef.empty())
    {
        custom_typedef.push_back(TypedefCorrespondance());
    }
    custom_typedef.back()[label] = typedef_spec;
}
