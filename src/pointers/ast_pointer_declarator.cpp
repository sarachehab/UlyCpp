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

int PointerDeclarator::GetDereferenceNumber() const
{
    PointerDeclarator *ptr = dynamic_cast<PointerDeclarator *>(direct_declarator_);

    if (ptr != nullptr)
    {
        return 1 + ptr->GetDereferenceNumber();
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
    int offset = dynamic_cast<Declarator *>(direct_declarator_)->GetScopeOffset();

    // Align offset to 4 bytes
    if (offset % 4 != 0)
    {
        offset += 4 - (offset % 4);
    }

    return offset;
}

bool PointerDeclarator::IsPointer() const
{
    return true;
}

void PointerDeclarator::DefineRoot(Node *declaration)
{
    if (direct_declarator_ == nullptr)
    {
        direct_declarator_ = declaration;
        return;
    }

    Declarator *declarator = dynamic_cast<Declarator *>(direct_declarator_);

    if (declarator != nullptr)
    {
        return declarator->DefineRoot(declaration);
    }

    throw std::runtime_error("PointerDeclarator::DefineRoot - not nullptr or Declarator");
}
