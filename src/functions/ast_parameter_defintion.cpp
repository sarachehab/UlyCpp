#include "../../include/functions/ast_parameter_definition.hpp"

void ParameterList::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    int register_number, int_register = 10, float_register = 42;
    std::string register_name;

    for (auto node : nodes_)
    {

        if (node == nullptr)
        {
            continue;
        }

        ParameterDeclaration *parameter = dynamic_cast<ParameterDeclaration *>(node);

        switch (parameter->GetType(context))
        {
        case Type::_CHAR:
        case Type::_SHORT:
        case Type::_INT:
        case Type::_UNSIGNED_INT:
        case Type::_LONG:
            register_number = int_register++;
            break;
        case Type::_FLOAT:
        case Type::_DOUBLE:
            register_number = float_register++;
            break;
        default:
            throw std::runtime_error("ParameterDeclaration::EmitRISC - Invalid type");
        }
        register_name = context.get_register_name(register_number);
        parameter->EmitRISC(stream, context, register_name);
    }
}

std::vector<Parameter> ParameterList::GetParameters(Context &context)
{
    int initial_offset = context.get_stack_offset();
    for (auto node : nodes_)
    {
        ParameterDeclaration *parameter = dynamic_cast<ParameterDeclaration *>(node);
        Parameter Parameter = parameter->GetParameter(context, initial_offset + GetScopeOffset());
        parameters.push_back(Parameter);
    }
    return parameters;
}

int ParameterList::GetScopeOffset() const
{
    int size = 0;
    for (Parameter Parameter : parameters)
    {
        size += Parameter.GetSize();
    }
    return size;
}

Type ParameterDeclaration::GetType(Context &context) const
{
    return dynamic_cast<TypeSpecifier *>(type_specifier_)->GetType();
}

void ParameterDeclaration::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    Type type = GetType(context);
    int offset = context.get_stack_offset();
    stream << context.store_instruction(type) << " " << passed_reg << ", " << offset << "(sp)" << std::endl;

    Variable variable_specs(false, false, type, Scope::_LOCAL, offset);
    context.define_variable(GetIdentifier(), variable_specs);

    context.increase_stack_offset(types_size.at(type));
}

void ParameterDeclaration::Print(std::ostream &stream) const
{
    type_specifier_->Print(stream);
    stream << " ";
    declarator_->Print(stream);
}

Parameter ParameterDeclaration::GetParameter(Context &context, int offset) const
{
    Type type = GetType(context);
    return Parameter(GetIdentifier(), false, false, type, offset);
}

int ParameterDeclaration::GetSize(Context &context) const
{
    return types_size.at(GetType(context));
}

std::string ParameterDeclaration::GetIdentifier() const
{
    return dynamic_cast<Identifier *>(declarator_)->GetIdentifier();
}
