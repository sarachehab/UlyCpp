#include "../../include/functions/ast_parameter_definition.hpp"

void ParameterList::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    int register_number, int_register = 10, float_register = 42;
    std::string register_name;

    // Iterate through list of parameters
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

        // Specify argument register for parameter
        register_name = context.get_register_name(register_number);

        // Emit parameter store instruction
        parameter->EmitRISC(stream, context, register_name);
    }
}

std::vector<Parameter> ParameterList::GetParameters(Context &context)
{
    int initial_offset = context.get_stack_offset();

    // Iterate through list of parameters
    for (auto node : nodes_)
    {
        // Append new parameter to list, specifying offset and type
        ParameterDeclaration *parameter = dynamic_cast<ParameterDeclaration *>(node);
        Parameter Parameter = parameter->GetParameter(context, initial_offset + GetScopeOffset());
        parameters.push_back(Parameter);
    }
    return parameters;
}

int ParameterList::GetScopeOffset() const
{
    int size = 0;

    // Iterate through list of parameters
    for (Parameter Parameter : parameters)
    {
        // Add size of parameter to total size
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
    // Get type of parameter declaration
    Type type = GetType(context);

    // Get stack offset for parameter
    int offset = context.get_stack_offset();

    // Store parameter on stack
    stream << context.store_instruction(type) << " " << passed_reg << ", " << offset << "(sp)" << std::endl;

    // Define parameter as variable accessible within function body
    Variable variable_specs(IsPointer(), false, type, offset, GetDereferenceNumber());
    context.define_variable(GetIdentifier(), variable_specs);

    // Increase stack offset to accomodate for parameter
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
    // Define parameter type for function
    if (IsPointer())
    {
        return Parameter(GetIdentifier(), true, false, GetType(context), offset, GetDereferenceNumber());
    }
    return Parameter(GetIdentifier(), false, false, GetType(context), offset, 0);
}

int ParameterDeclaration::GetSize(Context &context) const
{
    // Get size of parameter
    if (IsPointer())
    {
        types_size.at(Type::_INT);
    }

    return types_size.at(GetType(context));
}

std::string ParameterDeclaration::GetIdentifier() const
{
    Identifier *identifier = dynamic_cast<Identifier *>(declarator_);
    PointerDeclarator *pointer_declarator = dynamic_cast<PointerDeclarator *>(declarator_);

    if (identifier)
    {
        return identifier->GetIdentifier();
    }
    else if (pointer_declarator)
    {
        return pointer_declarator->GetIdentifier();
    }

    throw std::runtime_error("ParameterDeclaration::GetIdentifier() - declarator_ is not an Identifier or PointerDeclarator");
}

bool ParameterDeclaration::IsPointer() const
{

    if (dynamic_cast<PointerDeclarator *>(declarator_))
    {
        return true;
    }

    return false;
}

int ParameterDeclaration::GetDereferenceNumber() const
{
    // Get dereference number for parameter
    Declarator *declarator = dynamic_cast<Declarator *>(declarator_);

    if (declarator)
    {
        return declarator->GetDereferenceNumber();
    }

    return 0;
}
