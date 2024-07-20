#include "../include/ast_direct_declarator.hpp"

void DirectDeclarator::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    identifier_->EmitRISC(stream, context, passed_reg);
    stream << ":" << std::endl;
}

void DirectDeclarator::Print(std::ostream &stream) const
{
    identifier_->Print(stream);
}

std::string DirectDeclarator::GetIdentifier() const
{
    Identifier *id = dynamic_cast<Identifier *>(identifier_);
    return id->GetIdentifier();
}
