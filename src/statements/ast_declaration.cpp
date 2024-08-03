#include "../../include/statements/ast_declaration.hpp"

void Declaration::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    Type type = GetType();
    int type_size = types_size.at(type);

    NodeList *declarator_list = dynamic_cast<NodeList *>(declarator_list_);
    for (auto declarator : declarator_list->get_nodes())
    {
        Assignment *assignment = dynamic_cast<Assignment *>(declarator);
        Identifier *identifier = dynamic_cast<Identifier *>(declarator);
        DirectDeclarator *direct_declarator = dynamic_cast<DirectDeclarator *>(declarator);

        int offset = context.get_stack_offset();

        if (assignment != nullptr)
        {
            context.increase_stack_offset(type_size);
            std::string variable_name = assignment->GetIdentifier();
            Variable variable_specs(false, false, type, Scope::_LOCAL, offset);
            context.define_variable(variable_name, variable_specs);
            assignment->EmitRISC(stream, context, passed_reg);
        }
        else if (identifier != nullptr)
        {
            context.increase_stack_offset(type_size);
            std::string variable_name = identifier->GetIdentifier();
            Variable variable_specs(false, false, type, Scope::_LOCAL, offset);
            context.define_variable(variable_name, variable_specs);
        }
        else if (direct_declarator != nullptr)
        {
            std::string function_name = direct_declarator->GetIdentifier();

            ReturnValue return_value = ReturnValue(false, false, type);
            std::vector<Parameter> arguments = direct_declarator->GetParameters(context);
            Function function = Function(return_value, arguments);

            context.define_function(function_name, function);
        }
        else
        {
            throw std::runtime_error("Declaration EmitRISC: Unknown declarator type");
        }
    }
}

void Declaration::Print(std::ostream &stream) const
{
    type_specifier_->Print(stream);
    stream << " ";

    declarator_list_->Print(stream);
    stream << ";" << std::endl;
}

int Declaration::GetScopeOffset(Context &context) const
{
    TypeSpecifier *type_specifier = dynamic_cast<TypeSpecifier *>(type_specifier_);
    Type type = type_specifier->GetType();
    int type_size = types_size.at(type);

    NodeList *declarator_list = dynamic_cast<NodeList *>(declarator_list_);
    return type_size * declarator_list->get_nodes().size();
}

Type Declaration::GetType() const
{
    TypeSpecifier *type_specifier = dynamic_cast<TypeSpecifier *>(type_specifier_);
    return type_specifier->GetType();
}
