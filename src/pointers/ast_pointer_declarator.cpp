#include "../../include/pointers/ast_pointer_declarator.hpp"

std::string PointerDeclarator::GetIdentifier() const
{
    Identifier *identifier = dynamic_cast<Identifier *>(direct_declarator_);
    Declarator *declarator = dynamic_cast<Declarator *>(direct_declarator_);

    if (identifier)
    {
        return identifier->GetIdentifier();
    }
    else if (declarator)
    {
        return declarator->GetIdentifier();
    }

    throw std::runtime_error("PointerDeclarator::GetIdentifier - unrecognised type");
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

int PointerDeclarator::NumberPointers() const
{
    PointerDeclarator *ptr = dynamic_cast<PointerDeclarator *>(direct_declarator_);

    if (ptr != nullptr)
    {
        return 1 + ptr->NumberPointers();
    }
    return 1;
}

std::vector<Parameter> PointerDeclarator::GetParameters(Context &context) const
{
    return dynamic_cast<Declarator *>(direct_declarator_)->GetParameters(context);
}

void PointerDeclarator::StoreParameters(std::ostream &stream, Context &context, std::string passed_reg) const
{
    return dynamic_cast<Declarator *>(direct_declarator_)->StoreParameters(stream, context, passed_reg);
}

int PointerDeclarator::GetScopeOffset() const
{
    return dynamic_cast<Declarator *>(direct_declarator_)->GetScopeOffset();
}

bool PointerDeclarator::IsPointer() const
{
    return true;
}
