#include "../../include/context/context.hpp"

void Context::create_new_scope()
{
    variable_bindings.push_back(VariablesLayer());
    enums_correspondance.push_back(EnumsCorrespondance());
    custom_typedef.push_back(TypedefCorrespondance());

    // Set stack offset to the current stack offset, variables defined within this scope should be accessible.
    stack_offset.push(stack_offset.top());
}

void Context::pop_scope()
{
    if (!variable_bindings.empty())
    {
        variable_bindings.pop_back();
    }
    if (!enums_correspondance.empty())
    {
        enums_correspondance.pop_back();
    }
    if (!custom_typedef.empty())
    {
        custom_typedef.pop_back();
    }
    if (!stack_offset.empty())
    {
        stack_offset.pop();
    }
}

int Context::get_stack_offset() const
{
    return stack_offset.top() - total_offset;
}

void Context::increase_stack_offset(int offset)
{
    stack_offset.top() += offset;

    // Align stack offset to 4 bytes
    if (stack_offset.top() % 4 != 0)
    {
        stack_offset.top() += 4 - (stack_offset.top() % 4);
    }
}

void Context::set_stack_offset(int offset)
{
    total_offset = offset;

    // If stack not aligned...
    if (offset % 4 != 0)
    {
        std::runtime_error("Context::set_stack_offset: stack offset not aligned to 4 bytes");
    }
}
