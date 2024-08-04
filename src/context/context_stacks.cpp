#include "../../include/context/context.hpp"

void Context::create_new_scope()
{
    variable_bindings.push_back(VariablesLayer());

    // Set stack offset to the current stack offset, variables defined within this scope should be accessible.
    stack_offset.push(stack_offset.top());
}

void Context::pop_scope()
{
    if (variable_bindings.empty())
    {
        std::runtime_error("Error: trying to pop empty scope");
    }

    variable_bindings.pop_back();
    stack_offset.pop();
}

int Context::get_stack_offset() const
{
    return stack_offset.top();
}

void Context::increase_stack_offset(int offset)
{
    stack_offset.top() += offset;
}
