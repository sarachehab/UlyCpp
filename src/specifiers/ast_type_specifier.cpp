#include "../../include/specifiers/ast_type_specifier.hpp"

void TypeSpecifier::Print(std::ostream &stream) const
{
    std::string type;
    switch (type_)
    {
    case Type::_INT:
        type = "int";
        break;
    case Type::_UNSIGNED_INT:
        type = "unsigned int";
        break;
    case Type::_CHAR:
        type = "char";
        break;
    case Type::_SHORT:
        type = "short";
        break;
    case Type::_LONG:
        type = "long";
        break;
    case Type::_FLOAT:
        type = "float";
        break;
    case Type::_DOUBLE:
        type = "double";
        break;
    default:
        std::runtime_error("TypeSpecifier::Print: VOID not supported");
    }

    stream << type;
}

Type TypeSpecifier::GetType() const
{
    return type_;
}

void TypeSpecifier::DefineSpecifier() const
{
    // left empty
}
