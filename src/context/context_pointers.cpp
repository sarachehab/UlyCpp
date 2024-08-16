#include "../../include/context/context.hpp"

void Context::define_pointer(std::string identifier, Pointer pointer)
{
    pointer_bindings[identifier] = pointer;
}

Pointer Context::get_pointer(std::string identifier) const
{

    if (pointer_bindings.find(identifier) == pointer_bindings.end())
    {
        std::runtime_error("Context::GetPointer - no pointer found in PointerBindings");
    }

    return pointer_bindings.at(identifier);
}
