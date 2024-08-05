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
    // Check if variable is a global, and return specifications in the affirmative
    if (global_bindings.find(identifier) != global_bindings.end())
    {
        return global_bindings.at(identifier);
    }

    // Iterate through variable bindings in reverse order, from child scope to parent scope
    for (auto it = variable_bindings.rbegin(); it != variable_bindings.rend(); ++it)
    {
        if (it->find(identifier) != it->end())
        {
            return it->at(identifier);
        }
    }
    throw std::runtime_error("Context::get_variable - variable " + identifier + " not found");
}

bool Context::evaluating_expression() const
{
    return operation_type_stack.size() > 0;
}

void Context::define_global(std::string identifier, Global &global_specs)
{
    global_bindings[identifier] = global_specs;
}
