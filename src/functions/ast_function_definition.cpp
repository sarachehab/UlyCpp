#include "../../include/functions/ast_function_definition.hpp"

void FunctionDefinition::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    Declarator *direct_declarator_ = dynamic_cast<Declarator *>(declarator_);

    // Get function name
    std::string function_name = direct_declarator_->GetIdentifier();

    // Get function return type
    TypeSpecifier *return_type_specifier = dynamic_cast<TypeSpecifier *>(declaration_specifiers_);
    bool return_is_pointer = direct_declarator_->IsPointer();
    Type return_type = return_type_specifier->GetType();

    // Emit function header
    stream << ".text" << std::endl;
    stream << ".globl " << function_name << std::endl;
    stream << ".align " << types_shift.at(return_type) << std::endl;
    stream << ".type " << function_name << ", @function" << std::endl;
    stream << function_name << ":" << std::endl;

    // Define return value and parameters
    ReturnValue return_value(return_is_pointer, false, return_type);
    std::vector<Parameter> parameters = direct_declarator_->GetParameters(context);

    // Define function for later access in context, set offset to 0
    Function function(return_value, parameters);
    context.define_function(function_name, function);

    // Emit function body if available
    if (compound_statement_ != nullptr)
    {
        // Create new scope
        context.create_new_scope();
        context.set_operation_type(return_type);

        // Allocate stack space
        CompoundStatement *compound_statement = dynamic_cast<CompoundStatement *>(compound_statement_);

        // Estimate total offset for function stack allocation
        context.increase_stack_offset(8);
        int initial_offset = 8 + direct_declarator_->GetScopeOffset();
        int stack_allocated_space = compound_statement->GetScopeOffset(context) + initial_offset + 16;

        // Emit prelimnary register manipulations
        stream << "addi sp, sp, -" << stack_allocated_space << std::endl;
        stream << "sw ra, 0(sp)" << std::endl;
        stream << "sw s0, 4(sp)" << std::endl;
        direct_declarator_->StoreParameters(stream, context, passed_reg);
        stream << "addi s0, sp, " << stack_allocated_space << std::endl;

        compound_statement_->EmitRISC(stream, context, passed_reg);

        // Declare end of function body, jump here in case of return statement
        stream << context.get_last_function_end_statement() << ":" << std::endl;

        // Restore initial register values
        stream << "lw s0, 4(sp)" << std::endl;
        stream << "lw ra, 0(sp)" << std::endl;
        stream << "addi sp, sp, " << stack_allocated_space << std::endl;
        stream << "ret" << std::endl;

        // Pop scope
        context.pop_scope();
        context.pop_operation_type();
    }

    context.exit_function();
    stream << ".size " << function_name << ", .-" << function_name << std::endl;
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
