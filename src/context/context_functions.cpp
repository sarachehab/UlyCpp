#include "../../include/context/context.hpp"

void Context::define_function(std::string identifier, Function function)
{
    function_bindings[identifier] = function;
    last_function_end_statement = identifier + "_end";
    set_return_register(function.return_value.type);
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

void Context::set_return_register(Type type)
{
    switch (type)
    {
    case Type::_INT:
    case Type::_CHAR:
    case Type::_SHORT:
    case Type::_UNSIGNED_INT:
        return_register = "a0";
        break;
    case Type::_FLOAT:
    case Type::_DOUBLE:
    case Type::_LONG:
        return_register = "fa0";
        break;
    case Type::_VOID:
        throw std::runtime_error("Context::set_return_register: VOID not supported");
        break;
    default:
        std::cerr << "type: " << std::endl;
        std::cerr << static_cast<int>(type) << std::endl;
        throw std::runtime_error("Context::set_return_register: Invalid return type");
    }
}
