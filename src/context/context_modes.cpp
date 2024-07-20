#include "../../include/context/context.hpp"

void Context::mode_push(Mode mode)
{
    mode_stack.push(mode);
}

void Context::mode_pop()
{
    mode_stack.pop();
}

bool Context::has_mode(Mode mode) const
{
    if (mode_stack.empty())
    {
        std::runtime_error("Context::has_mode - mode stack is empty");
    }
    return mode_stack.top() == mode;
}