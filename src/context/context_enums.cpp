#include "../../include/context/context.hpp"

void Context::define_enum(std::string enum_name, std::vector<std::string> enum_labels)
{
    enums_definitions[enum_name] = enum_labels;
}

void Context::define_enum_label_value_correspondance(std::string enum_label, int value)
{
    if (enums_correspondance.empty())
    {
        throw std::runtime_error("Context::define_enum_label_value_correspondance - No active scope in enums_correspondance");
    }
    enums_correspondance.back()[enum_label] = value;
}

bool Context::is_enum(std::string identifier)
{
    // Iterate through variable bindings in reverse order, from child scope to parent scope
    for (auto it = enums_correspondance.rbegin(); it != enums_correspondance.rend(); ++it)
    {
        if (it->find(identifier) != it->end())
        {
            return true;
        }
    }

    return false;
}

int Context::get_enum_value(std::string label)
{
    // Iterate through variable bindings in reverse order, from child scope to parent scope
    for (auto it = enums_correspondance.rbegin(); it != enums_correspondance.rend(); ++it)
    {
        if (it->find(label) != it->end())
        {
            return it->at(label);
        }
    }
    throw std::runtime_error("Context::GetEnumValue - enum value not found in bindings");
}
