#include "../include/ast_direct_declarator.hpp"

void DirectDeclarator::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Emit function label
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
    Identifier *identifier = dynamic_cast<Identifier *>(identifier_);
    Declarator *declarator = dynamic_cast<Declarator *>(identifier_);

    if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    else if (declarator != nullptr)
    {
        return declarator->GetIdentifier();
    }

    throw std::runtime_error("DirectDeclarator::GetIdentifier() - unrecognised identifier_");
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
    // No parameters for function: no need to account for them
    if (parameter_list_ == nullptr)
    {
        return 0;
    }

    // Function has parameters: account for them when allocating stack space
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

bool DirectDeclarator::IsPointer() const
{
    return false;
}

int DirectDeclarator::GetDereferenceNumber() const
{
    Declarator *declarator = dynamic_cast<Declarator *>(identifier_);
    if (declarator)
    {
        return declarator->GetDereferenceNumber();
    }

    return 0;
}

void DirectDeclarator::DefineRoot(Node *declaration)
{
    throw std::runtime_error("ArrayDeclarator::DefineRoot not implemented");
}
