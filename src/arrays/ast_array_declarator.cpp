#include "../../include/arrays/ast_array_declarator.hpp"

std::string ArrayDeclarator::GetIdentifier() const
{
    return dynamic_cast<Identifier *>(identifier_)->GetIdentifier();
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
