#include "../../include/functions/ast_function_definition.hpp"

void FunctionDefinition::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{

    DirectDeclarator *direct_declarator_ = dynamic_cast<DirectDeclarator *>(declarator_);
    std::string function_name = direct_declarator_->GetIdentifier();

    TypeSpecifier *return_type_specifier = dynamic_cast<TypeSpecifier *>(declaration_specifiers_);
    Type return_type = return_type_specifier->GetType();

    stream << ".text" << std::endl;
    stream << ".globl " << function_name << std::endl;
    stream << ".type " << function_name << ", @function" << std::endl;
    stream << function_name << ":" << std::endl;

    // TODO: Create new function in context with arguments and return valud
    ReturnValue return_value(false, false, return_type);
    std::vector<Argument> arguments = {};
    Function function(return_value, arguments);
    context.define_function(function_name, function);

    if (compound_statement_ != nullptr)
    {
        compound_statement_->EmitRISC(stream, context, passed_reg);
    }
}

void FunctionDefinition::Print(std::ostream &stream) const
{
    declaration_specifiers_->Print(stream);
    stream << " ";

    declarator_->Print(stream);
    stream << "() {" << std::endl;

    if (compound_statement_ != nullptr)
    {
        compound_statement_->Print(stream);
    }
    stream << "}" << std::endl;
}
