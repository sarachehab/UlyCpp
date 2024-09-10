#include "../../include/context/context.hpp"

int Context::label_counter = 0;

std::vector<EnumsCorrespondance> Context::enums_correspondance = {EnumsCorrespondance()};
std::vector<TypedefCorrespondance> Context::custom_typedef = {TypedefCorrespondance()};

Context::Context()
{
    stack_offset.push(0);
    allocated_registers.push(std::set<int>());

    // Ensure there's always a default EnumsCorrespondance available
    enums_correspondance.push_back(EnumsCorrespondance());
    custom_typedef.push_back(TypedefCorrespondance());
}

Context::~Context()
{
}
