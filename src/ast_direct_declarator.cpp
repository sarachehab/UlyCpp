#include "../include/ast_direct_declarator.hpp"

void DirectDeclarator::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    identifier_->EmitRISC(stream, context, passed_reg);
    stream << ":" << std::endl;
}

void DirectDeclarator::Print(std::ostream &stream) const
{
    identifier_->Print(stream);
    if (parameter_list_ != nullptr)
    {
        stream << "(";
        parameter_list_->Print(stream);
        stream << ")";
    }
}

std::string DirectDeclarator::GetIdentifier() const
{
    Identifier *id = dynamic_cast<Identifier *>(identifier_);
    return id->GetIdentifier();
}

std::vector<Parameter> DirectDeclarator::GetParameters(Context &context) const
{
    if (parameter_list_ == nullptr)
    {
        return std::vector<Parameter>();
    }
    else
    {
        ParameterList *parameter_list = dynamic_cast<ParameterList *>(parameter_list_);
        return parameter_list->GetParameters(context);
    }
}

int DirectDeclarator::GetScopeOffset() const
{
    if (parameter_list_ == nullptr)
    {
        return 0;
    }
    else
    {
        ParameterList *parameter_list = dynamic_cast<ParameterList *>(parameter_list_);
        return parameter_list->GetScopeOffset();
    }
}

void DirectDeclarator::StoreParameters(std::ostream &stream, Context &context, std::string passed_reg) const
{
    if (parameter_list_ != nullptr)
    {
        ParameterList *parameter_list = dynamic_cast<ParameterList *>(parameter_list_);
        parameter_list->EmitRISC(stream, context, passed_reg);
    }
}
