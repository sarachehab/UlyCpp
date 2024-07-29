#include "../../include/context/context.hpp"

void Context::set_operation_type(Type type) { operation_type_stack.push(type); }

void Context::pop_operation_type() { operation_type_stack.pop(); }

Type Context::get_operation_type() const { return operation_type_stack.top(); }
