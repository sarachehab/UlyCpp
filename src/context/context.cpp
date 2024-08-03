#include "../../include/context/context.hpp"

Context::Context()
{
    label_counter = 0;
    stack_offset.push(0);
    allocated_registers.push(std::set<int>());
}

Context::~Context()
{
}
