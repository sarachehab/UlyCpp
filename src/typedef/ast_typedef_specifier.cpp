#include "../../include/typedef/ast_typedef_specifier.hpp"

std::string TypedefSpecifier::GetIdentifier() const
{
    return type_name_;
}

void TypedefSpecifier::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // left empty
}

void TypedefSpecifier::Print(std::ostream &stream) const
{
    stream << type_name_ << " ";
}

void TypedefSpecifier::DefineSpecifier()
{
    typedef_spec = Context::get_typedef_spec(GetIdentifier());

    switch (typedef_spec.type_)
    {
    case Type::_STRUCT:
        throw std::runtime_error("TypedefSpecifier::GetSpecifier - only PRIMITIVE implemented");
    case Type::_CHAR:
    case Type::_SHORT:
    case Type::_UNSIGNED_INT:
    case Type::_INT:
    case Type::_LONG:
    case Type::_FLOAT:
    case Type::_DOUBLE:
        typedef_specifier_ = new TypeSpecifier(typedef_spec.type_);
        break;
    default:
        throw std::runtime_error("TypedefSpecifier::GetSpecifier - nor PRIMITIVE nor STRUCT");
    }
}

Specifier *TypedefSpecifier::GetSpecifier() const
{
    return typedef_specifier_;
}

Declarator *TypedefSpecifier::GetRootNode() const
{
    if (typedef_spec.number_pointers_ < 0)
    {
        throw std::runtime_error("TypedefSpecifier::ConvertNode - number of pointers should not be smaller than 0");
    }

    Declarator *node = nullptr;

    for (int i = 0; i < typedef_spec.number_pointers_; i++)
    {
        node = new PointerDeclarator(node);
    }

    return node;
}

Type TypedefSpecifier::GetType() const
{
    if (typedef_spec.type_ == Type::_STRUCT)
    {
        throw std::runtime_error(" TypedefSpecifier::GetType - Struct not supported");
    }

    return typedef_spec.type_;
}

void TypedefSpecifier::DefineSpecifier() const
{
    // left empty
}
