#include "../../include/context/context.hpp"

void Context::define_variable(std::string identifier, Variable variable)
{
    if (variable_bindings.empty())
    {
        throw std::runtime_error("Context::define_variable - trying to define variable in empty scope");
    }
    variable_bindings.back()[identifier] = variable;
}

Variable Context::get_variable(std::string identifier) const
{
    for (auto it = variable_bindings.rbegin(); it != variable_bindings.rend(); ++it)
    {
        if (it->find(identifier) != it->end())
        {
            return it->at(identifier);
        }
    }
    throw std::runtime_error("Context::get_variable - variable " + identifier + " not found");
}