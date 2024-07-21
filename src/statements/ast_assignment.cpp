#include "../../include/statements/ast_assignment.hpp"

void Assignment::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    Variable variable_specs = context.get_variable(GetIdentifier());
    Type type = variable_specs.type;
    int offset = variable_specs.offset;

    std::string reg = context.get_register(type);
    expression_->EmitRISC(stream, context, reg);

    stream << context.store_instruction(type) << " " << reg << ", " << offset << "(s0)" << std::endl;
    context.deallocate_register(reg);
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
