#include "../../include/context/context.hpp"

void Global::push_lower(uint32_t value)
{
    lower_values.push_back(value);
}

void Global::push_upper(uint32_t value)
{
    upper_values.push_back(value);
}

void Global::print_global(std::ostream &stream) const
{
    int i;

    for (i = 0; i < lower_values.size(); i++)
    {
        stream << "\t" << assembler_directives.at(type) << " " << lower_values.at(i) << std::endl;

        if (type == Type::_DOUBLE)
        {
            stream << "\t" << assembler_directives.at(type) << " " << upper_values.at(i) << std::endl;
        }
    }

    while (i < size_array)
    {
        stream << "\t.zero " << types_size.at(type) << std::endl;
        i++;
    }
}

void Context::print_global(std::ostream &stream) const
{
    stream << "\t.data" << std::endl;

    for (auto global : global_bindings)
    {
        stream << "\t.align " << types_shift.at(global.second.type) << std::endl;
        stream << "\t.type global_" << global.first << ", @object" << std::endl;
        stream << "\t.globl global_" << global.first << std::endl;

        stream << "global_" << global.first << ":" << std::endl;
        global.second.print_global(stream);
        stream << std::endl;
    }
}
