#include "../../include/arrays/ast_array_declarator.hpp"

std::string ArrayDeclarator::GetIdentifier() const
{
    Identifier *identifier = dynamic_cast<Identifier *>(identifier_);
    Declarator *declarator = dynamic_cast<Declarator *>(identifier_);

    if (declarator != nullptr)
    {
        return declarator->GetIdentifier();
    }

    else if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }

    throw std::runtime_error("ArrayDeclarator GetIdentifier: Identifier not found");
}

int ArrayDeclarator::GetSize(Context &context) const
{
    if (constant_expression_ == nullptr)
    {
        return -1;
    }

    IntConstant *int_constant = dynamic_cast<IntConstant *>(constant_expression_);

    if (int_constant != nullptr)
    {
        return int_constant->GetValue();
    }

    throw std::runtime_error("ArrayDeclarator::GetSize - constant_expression neither enumerator nor constant");
}

void ArrayDeclarator::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // nothing to do here
}

void ArrayDeclarator::Print(std::ostream &stream) const
{
    identifier_->Print(stream);
    stream << "[";
    if (constant_expression_ != nullptr)
    {
        constant_expression_->Print(stream);
    }
    stream << "]";
}

bool ArrayDeclarator::IsPointer() const
{
    return dynamic_cast<PointerDeclarator *>(identifier_) != nullptr;
}

std::vector<Parameter> ArrayDeclarator::GetParameters(Context &context) const
{
    return dynamic_cast<Declarator *>(identifier_)->GetParameters(context);
}

int ArrayDeclarator::GetScopeOffset() const
{
    return dynamic_cast<Declarator *>(identifier_)->GetScopeOffset();
}

void ArrayDeclarator::StoreParameters(std::ostream &stream, Context &context, std::string passed_reg) const
{
    return dynamic_cast<Declarator *>(identifier_)->StoreParameters(stream, context, passed_reg);
}

int ArrayDeclarator::GetDereferenceNumber() const
{
    Declarator *declarator = dynamic_cast<Declarator *>(identifier_);
    if (declarator)
    {
        return declarator->GetDereferenceNumber();
    }

    return 0;
}

void ArrayDeclarator::DefineRoot(Node *declaration)
{
    if (identifier_ == nullptr)
    {
        identifier_ = declaration;
        return;
    }

    Declarator *declarator = dynamic_cast<Declarator *>(identifier_);

    if (declarator != nullptr)
    {
        return declarator->DefineRoot(declaration);
    }

    throw std::runtime_error("PointerDeclarator::DefineRoot - not nullptr or Declarator");
}
