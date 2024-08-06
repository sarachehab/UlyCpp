#include "../../include/arrays/ast_array_declarator.hpp"

std::string ArrayDeclarator::GetIdentifier() const
{
    Identifier *identifier = dynamic_cast<Identifier *>(identifier_);
    PointerDeclarator *pointer_declarator = dynamic_cast<PointerDeclarator *>(identifier_);

    if (pointer_declarator != nullptr)
    {
        return pointer_declarator->GetIdentifier();
    }

    else if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }

    throw std::runtime_error("ArrayDeclarator GetIdentifier: Identifier not found");
}

int ArrayDeclarator::GetSize() const
{
    if (constant_expression_ == nullptr)
    {
        return -1;
    }
    return dynamic_cast<IntConstant *>(constant_expression_)->GetValue();
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
