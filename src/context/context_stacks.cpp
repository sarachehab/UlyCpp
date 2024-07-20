#include "../../include/context/context.hpp"

void Context::create_new_scope()
{
    variable_bindings.push_back(VariablesLayer());
    current_stack_offset = 0;
}

void Context::pop_scope()
{
    if (variable_bindings.empty())
    {
        std::runtime_error("Error: trying to pop empty scope");
    }
    variable_bindings.pop_back();
}

int Context::get_stack_offset() const
{
    return current_stack_offset;
}

void Context::increase_stack_offset(int offset)
{
    current_stack_offset += offset;
}