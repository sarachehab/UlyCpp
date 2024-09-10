#include "../../include/typedef/ast_typedef_definition.hpp"

void TypedefDefinition::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // left empty
}

void TypedefDefinition::Print(std::ostream &stream) const
{
    stream << "typedef ";
    declaration_specifier_->Print(stream);
    stream << " ";
}

void TypedefDefinition::DefineTypedef(NodeList *aliases)
{

    for (auto alias : aliases->get_nodes())
    {
        int pointer = initial_number_pointers;
        std::string alias_name;

        PointerDeclarator *pointer_declarator = dynamic_cast<PointerDeclarator *>(alias);
        AddressOf *address_of = dynamic_cast<AddressOf *>(alias);
        ArrayDeclarator *array_declarator = dynamic_cast<ArrayDeclarator *>(alias);
        Identifier *identifier = dynamic_cast<Identifier *>(alias);

        if (pointer_declarator != nullptr)
        {
            pointer += pointer_declarator->GetDereferenceNumber();
            alias_name = pointer_declarator->GetIdentifier();
        }
        else if (address_of != nullptr)
        {
            pointer -= address_of->GetAddressOfCount();
            alias_name = address_of->GetIdentifier();
        }
        else if (array_declarator != nullptr)
        {
            alias_name = array_declarator->GetIdentifier();
            pointer += array_declarator->GetDereferenceNumber();
            throw std::runtime_error("TypedefDefinition::DefineTypedef - ArrayDeclarator not implemented");
        }
        else if (identifier != nullptr)
        {
            alias_name = identifier->GetIdentifier();
        }

        TypedefSpec typedef_spec;

        switch (type)
        {
        case Type::_STRUCT:
            throw std::runtime_error("TypedefDefinition::DefineTypedef - alias is not a PRIMITIVE");
        case Type::_CHAR:
        case Type::_SHORT:
        case Type::_UNSIGNED_INT:
        case Type::_INT:
        case Type::_LONG:
        case Type::_FLOAT:
        case Type::_DOUBLE:
            typedef_spec = TypedefSpec(type, pointer);
            break;
        default:
            throw std::runtime_error("TypedefDefinition::DefineTypedef - alias is not a PRIMITIVE nor a STRUCT");
        }

        Context::define_typedef(alias_name, typedef_spec);
    }
}

void TypedefDefinition::ExtractDeclarationSpecifier()
{
    Specifier *specifier = dynamic_cast<Specifier *>(declaration_specifier_);

    if (specifier != nullptr)
    {
        type = specifier->GetType();
    }

    else
    {
        throw std::runtime_error("TypedefDefinition::ExtractDeclarationSpecifier - DeclarationSpecifier is not a typedef nor a standard specifier");
    }
}
