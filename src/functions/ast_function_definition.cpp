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

    // TODO: Create new function in context with arguments and return value
    ReturnValue return_value(false, false, return_type);
    std::vector<Argument> arguments = {};
    Function function(return_value, arguments);
    context.define_function(function_name, function);

    if (compound_statement_ != nullptr)
    {
        // Allocate stack space
        CompoundStatement *compound_statement = dynamic_cast<CompoundStatement *>(compound_statement_);
        int stack_allocated_space = compound_statement->GetScopeOffset(context) + 8;

        stream << "addi sp, sp, -" << stack_allocated_space << std::endl;
        stream << "sw ra, 0(sp)" << std::endl;
        stream << "sw s0, 4(sp)" << std::endl;
        stream << "addi s0, sp, " << stack_allocated_space << std::endl;
        context.set_initial_offset(8);

        compound_statement_->EmitRISC(stream, context, passed_reg);

        stream << context.get_last_function_end_statement() << ":" << std::endl;
        stream << "lw s0, 4(sp)" << std::endl;
        stream << "lw ra, 0(sp)" << std::endl;
        stream << "addi sp, sp, " << stack_allocated_space << std::endl;
        stream << "ret" << std::endl;
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
