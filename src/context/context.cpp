#include "../../include/context/context.hpp"

int Context::label_counter = 0;

Context::Context()
{
    stack_offset.push(0);
    allocated_registers.push(std::set<int>());
}

Context::~Context()
{
}
