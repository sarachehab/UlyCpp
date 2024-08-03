#include "../../include/context/context.hpp"

int Parameter::GetSize() const
{
    return types_size.at(type);
}

void Context::define_function(std::string identifier, Function function)
{
    function_bindings[identifier] = function;
    last_function_end_statement = identifier + "_end";
    set_return_register(function.return_value.type);
    stack_offset.push(0);
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

void Context::set_function_call(std::string function)
{
    function_call_stack.push(function);
    allocated_registers.push(std::set<int>());
}

void Context::pop_function_call()
{
    function_call_stack.pop();
    allocated_registers.pop();
}

Function Context::get_function_call() const
{
    if (function_call_stack.empty())
    {
        throw std::runtime_error("Context::get_function_call - no function call");
    }
    return get_function(function_call_stack.top());
}

void Context::exit_function()
{
    stack_offset.pop();
}
