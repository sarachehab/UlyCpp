#include "../../include/context/context.hpp"

void Context::define_function(std::string identifier, Function function)
{
    function_bindings[identifier] = function;
    last_function_end_statement = identifier + "_end";
}

Function Context::get_function(std::string identifier) const
{
    if (function_bindings.find(identifier) == function_bindings.end())
    {
        throw std::runtime_error("Context::get_function - function " + identifier + " not found");
    }
    return function_bindings.at(identifier);
}

std::string Context::get_last_function_end_statement() const
{
    if (last_function_end_statement.empty())
    {
        throw std::runtime_error("Context::get_last_function_end_statement - no function defined");
    }
    return last_function_end_statement;
}