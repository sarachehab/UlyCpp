#include "../../include/primitives/ast_identifier.hpp"

void Identifier::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Fetch variable from memory if expression is being evaluated
    if (context.evaluating_expression())
    {
        // Fetch variable specifications
        Variable variable_specs = context.get_variable(identifier_);
        Type type = variable_specs.type;

        // Load variable from memory specified in variable bindings if local scope
        if (variable_specs.scope == Scope::_LOCAL)
        {
            int offset = variable_specs.offset;

            // Load variable from specified memory location
            stream << context.load_instruction(type) << " " << passed_reg << ", " << offset << "(sp)" << std::endl;
        }

        // Load variable from label-specified memory location if global scope
        else if (variable_specs.scope == Scope::_GLOBAL)
        {
            std::string global_memory_location = "global_" + identifier_;
            std::string global_memory_register = context.get_register(Type::_INT);

            // Access global memory by targetting global label
            stream << "lui " << global_memory_register << ", " << "%hi(" << global_memory_location << ")" << std::endl;
            stream << context.load_instruction(type) << " " << passed_reg << ", %lo(" << global_memory_location << ")(" << global_memory_register << ")" << std::endl;
            context.deallocate_register(global_memory_register);
        }

        else
        {
            throw std::runtime_error("Identifier EmitRISC: Invalid scope");
        }
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
