#include "../../include/primitives/ast_identifier.hpp"

void Identifier::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Fetch variable from memory if expression is being evaluated
    if (context.evaluating_expression())
    {
        // Fetch variable specifications
        Variable variable_specs = context.get_variable(identifier_);
        Type type = variable_specs.type;
        int offset = variable_specs.offset;

        // Load variable from specified memory location
        stream << context.load_instruction(type) << " " << passed_reg << ", " << offset << "(sp)" << std::endl;
    }
}

void Identifier::Print(std::ostream &stream) const
{
    stream << identifier_;
};

std::string Identifier::GetIdentifier() const
{
    return identifier_;
}

Type Identifier::GetType(Context &context) const
{
    return context.get_variable(identifier_).type;
}
