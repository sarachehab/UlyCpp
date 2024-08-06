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
    PointerDeclarator *pointer_declarator = dynamic_cast<PointerDeclarator *>(identifier_);
    ArrayDeclarator *array_declarator = dynamic_cast<ArrayDeclarator *>(identifier_);

    if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    else if (pointer_declarator != nullptr)
    {
        return pointer_declarator->GetIdentifier();
    }
    else if (array_declarator != nullptr)
    {
        return array_declarator->GetIdentifier();
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

void Declarator::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    direct_declarator_->EmitRISC(stream, context, passed_reg);
}

void Declarator::Print(std::ostream &stream) const
{
    direct_declarator_->Print(stream);
}

std::string Declarator::GetIdentifier() const
{
    DirectDeclarator *direct_declarator = dynamic_cast<DirectDeclarator *>(direct_declarator_);
    PointerDeclarator *pointer_declarator = dynamic_cast<PointerDeclarator *>(direct_declarator_);
    Identifier *identifier = dynamic_cast<Identifier *>(direct_declarator);
    ArrayDeclarator *array_declarator = dynamic_cast<ArrayDeclarator *>(direct_declarator);
    Declarator *declarator = dynamic_cast<Declarator *>(direct_declarator);

    if (pointer_declarator != nullptr)
    {
        return pointer_declarator->GetIdentifier();
    }
    else if (direct_declarator != nullptr)
    {
        return direct_declarator->GetIdentifier();
    }
    else if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    else if (array_declarator != nullptr)
    {
        return array_declarator->GetIdentifier();
    }
    else if (declarator != nullptr)
    {
        return declarator->GetIdentifier();
    }

    throw std::runtime_error("Declarator::GetIdentifier() - no identifier found");
}

std::vector<Parameter> Declarator::GetParameters(Context &context) const
{
    DirectDeclarator *direct_declarator = dynamic_cast<DirectDeclarator *>(direct_declarator_);
    Declarator *declarator = dynamic_cast<Declarator *>(direct_declarator);

    if (declarator != nullptr)
    {
        return declarator->GetParameters(context);
    }

    if (direct_declarator != nullptr)
    {
        return direct_declarator->GetParameters(context);
    }

    throw std::runtime_error("Declarator::GetParameters() - no parameters found");
}

int Declarator::GetScopeOffset() const
{
    DirectDeclarator *direct_declarator = dynamic_cast<DirectDeclarator *>(direct_declarator_);
    Declarator *declarator = dynamic_cast<Declarator *>(direct_declarator);

    if (declarator != nullptr)
    {
        return declarator->GetScopeOffset();
    }

    if (direct_declarator != nullptr)
    {
        return direct_declarator->GetScopeOffset();
    }

    throw std::runtime_error("Declarator::GetScopeOffset() - no scope offset found");
}

void Declarator::StoreParameters(std::ostream &stream, Context &context, std::string passed_reg) const
{
    DirectDeclarator *direct_declarator = dynamic_cast<DirectDeclarator *>(direct_declarator_);
    Declarator *declarator = dynamic_cast<Declarator *>(direct_declarator);

    if (declarator != nullptr)
    {
        return declarator->StoreParameters(stream, context, passed_reg);
    }

    if (direct_declarator != nullptr)
    {
        return direct_declarator->StoreParameters(stream, context, passed_reg);
    }

    throw std::runtime_error("Declarator::StoreParameters() - no parameters found");
}

bool Declarator::IsPointer() const
{
    if (dynamic_cast<PointerDeclarator *>(direct_declarator_) != nullptr)
    {
        return true;
    }

    else if (dynamic_cast<Declarator *>(direct_declarator_) != nullptr)
    {
        return dynamic_cast<Declarator *>(direct_declarator_)->IsPointer();
    }

    return false;
}
