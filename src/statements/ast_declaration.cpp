#include "../../include/statements/ast_declaration.hpp"

void Declaration::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    TypeSpecifier *type_specifier = dynamic_cast<TypeSpecifier *>(type_specifier_);
    Type type = type_specifier->GetType();
    int type_size = context.types_size.at(type);

    NodeList *declarator_list = dynamic_cast<NodeList *>(declarator_list_);
    for (auto declarator : declarator_list->get_nodes())
    {
        Assignment *assignment = dynamic_cast<Assignment *>(declarator);
        Identifier *identifier = dynamic_cast<Identifier *>(declarator);

        int offset = context.get_stack_offset();
        context.increase_stack_offset(type_size);

        if (assignment != nullptr)
        {
            std::string variable_name = assignment->GetIdentifier();
            assignment->EmitRISC(stream, context, passed_reg);
            Variable variable_specs(false, false, type, Scope::_LOCAL, offset);
            context.define_variable(variable_name, variable_specs);
        }
        else if (identifier != nullptr)
        {
            std::string variable_name = identifier->GetIdentifier();
            Variable variable_specs(false, false, type, Scope::_LOCAL, offset);
            context.define_variable(variable_name, variable_specs);
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
    int type_size = context.types_size.at(type);

    NodeList *declarator_list = dynamic_cast<NodeList *>(declarator_list_);
    return type_size * declarator_list->get_nodes().size();
}
