#include "../../include/pointers/ast_pointer_declarator.hpp"

std::string PointerDeclarator::GetIdentifier() const
{
    Identifier *identifier = dynamic_cast<Identifier *>(direct_declarator_);
    PointerDeclarator *pointer_declarator = dynamic_cast<PointerDeclarator *>(direct_declarator_);

    if (identifier)
    {
        identifier->GetIdentifier();
    }
    else if (pointer_declarator)
    {
        pointer_declarator->GetIdentifier();
    }

    throw std::runtime_error("PointerDeclarator::GetIdentifier() - direct_declarator_ is not an Identifier or PointerDeclarator");
}

void PointerDeclarator::EmitRISC(std::ostream &stream, Context &context, std::string passed_register) const
{
    // unsused
}

void PointerDeclarator::Print(std::ostream &stream) const
{
    stream << "*";
    direct_declarator_->Print(stream);
}

Type PointerDeclarator::GetType() const
{
    return Type::_INT;
}
