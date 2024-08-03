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

    ReturnValue return_value(false, false, return_type);
    std::vector<Parameter> parameters = direct_declarator_->GetParameters(context);
    Function function(return_value, parameters);
    context.define_function(function_name, function);

    if (compound_statement_ != nullptr)
    {
        context.create_new_scope();
        context.set_operation_type(return_type);

        // Allocate stack space
        CompoundStatement *compound_statement = dynamic_cast<CompoundStatement *>(compound_statement_);

        context.increase_stack_offset(8);
        int initial_offset = 8 + direct_declarator_->GetScopeOffset();

        int stack_allocated_space = compound_statement->GetScopeOffset(context) + initial_offset;

        stream << "addi sp, sp, -" << stack_allocated_space << std::endl;
        stream << "sw ra, 0(sp)" << std::endl;
        stream << "sw s0, 4(sp)" << std::endl;
        direct_declarator_->StoreParameters(stream, context, passed_reg);
        stream << "addi s0, sp, " << stack_allocated_space << std::endl;

        compound_statement_->EmitRISC(stream, context, passed_reg);

        stream << context.get_last_function_end_statement() << ":" << std::endl;
        stream << "lw s0, 4(sp)" << std::endl;
        stream << "lw ra, 0(sp)" << std::endl;
        stream << "addi sp, sp, " << stack_allocated_space << std::endl;
        stream << "ret" << std::endl;

        context.pop_operation_type();
        context.pop_scope();
    }

    context.exit_function();
}

void FunctionDefinition::Print(std::ostream &stream) const
{
    declaration_specifiers_->Print(stream);
    stream << " ";

    declarator_->Print(stream);
    stream << "{" << std::endl;

    if (compound_statement_ != nullptr)
    {
        compound_statement_->Print(stream);
    }
    stream << "}" << std::endl;
}
