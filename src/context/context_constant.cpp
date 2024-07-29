#include "../../include/context/context_constant.hpp"
#include "../../include/context/context.hpp"

void ContextConstant::PrintConstant(std::ostream &stream) const
{
    switch (type_)
    {
    case Type::_FLOAT:
        stream << assembler_directives.at(Type::_FLOAT) << " " << lower_int << std::endl;
        break;

    case Type::_DOUBLE:
        stream << assembler_directives.at(Type::_DOUBLE) << " " << lower_int << std::endl;
        stream << assembler_directives.at(Type::_DOUBLE) << " " << upper_int << std::endl;
        break;

    default:
        throw std::runtime_error("ContextConstant::PrintConstant: Invalid type");
    }
}

int Context::declare_constant(float value)
{
    ContextConstant constant(value);
    constant_declarations.push_back(constant);
    return constant_declaration_number++;
}

int Context::declare_constant(double value)
{
    ContextConstant constant(value);
    constant_declarations.push_back(constant);
    return constant_declaration_number++;
}

void Context::print_constant_declarations(std::ostream &stream) const
{
    int i = 0;
    for (const auto &constant : constant_declarations)
    {
        stream << ".constant_representation_" << i++ << ":" << std::endl;
        constant.PrintConstant(stream);
    }
}
