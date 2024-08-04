#include "../../include/statements/ast_assignment.hpp"

void Assignment::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Get variable specifications
    Variable variable_specs = context.get_variable(GetIdentifier());
    Type type = variable_specs.type;

    // Get offset of variable within current stack frame
    int offset = variable_specs.offset;

    // Define operation type for expression
    context.set_operation_type(type);

    // Emit expression to specified register
    std::string reg = context.get_register(type);
    expression_->EmitRISC(stream, context, reg);

    // Spill value to memory
    stream << context.store_instruction(type) << " " << reg << ", " << offset << "(sp)" << std::endl;

    // Deallocate register
    context.deallocate_register(reg);

    // Pop operation type
    context.pop_operation_type();
}

void Assignment::Print(std::ostream &stream) const
{
    unary_expression_->Print(stream);
    stream << " = ";
    expression_->Print(stream);
    stream << ";" << std::endl;
}

std::string Assignment::GetIdentifier() const
{
    Identifier *identifier = dynamic_cast<Identifier *>(unary_expression_);
    if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    throw std::runtime_error("Assignment GetIdentifier: Not an identifier");
}
