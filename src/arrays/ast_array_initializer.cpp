#include "../../include/arrays/ast_array_initializer.hpp"

int ArrayInitializer::GetSize() const
{
    return dynamic_cast<NodeList *>(initializer_list_)->get_nodes().size();
}

void ArrayInitializer::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Unused
}

void ArrayInitializer::Print(std::ostream &stream) const
{
    stream << "{ ";
    initializer_list_->Print(stream);
    stream << " }";
}

void ArrayInitializer::Save(std::ostream &stream, Context &context, Variable variable_specs, std::string identifier) const
{
    int offset;
    Type type = variable_specs.type;
    std::string passed_reg = context.get_register(type);

    // If local scope, save array to stack by accessing variable offset through variable bindings
    if (variable_specs.scope == Scope::_LOCAL)
    {
        // Set initial offset to variable offset within current stack frame, will be increased as we iterate through initializer list
        offset = variable_specs.offset;

        // Iterate through initializer list and save each element to the stack
        for (auto initializer : dynamic_cast<NodeList *>(initializer_list_)->get_nodes())
        {
            dynamic_cast<Operand *>(initializer)->EmitRISC(stream, context, passed_reg);

            stream << context.store_instruction(type) << " " << passed_reg << ", " << offset << "(s0)" << std::endl;

            // Increase offset to get next element in array
            offset += types_size.at(type);
        }
    }

    // If global scope, save array to stack by targeting global label
    else if (variable_specs.scope == Scope::_GLOBAL)
    {
        std::string global_memory_location = "global_" + identifier;
        std::string global_memory_register = context.get_register(Type::_INT);

        // Access global memory by targetting global label
        stream << "lui " << global_memory_register << ", " << "%hi(" << global_memory_location << ")" << std::endl;
        stream << "addi " << global_memory_register << ", " << "%lo(" << global_memory_location << ")" << std::endl;

        // Set initial offset to 0, will be increased as we iterate through initializer list
        offset = 0;

        // Iterate through initializer list and save each element to global memory
        for (auto initializer : dynamic_cast<NodeList *>(initializer_list_)->get_nodes())
        {
            dynamic_cast<Operand *>(initializer)->EmitRISC(stream, context, passed_reg);

            stream << context.store_instruction(type) << " " << passed_reg << ", " << offset << "(" << global_memory_register << ")" << std::endl;

            // Increase offset to get next element in array
            offset += types_size.at(type);
        }

        context.deallocate_register(global_memory_register);
    }

    else
    {
        throw std::runtime_error("ArrayInitializer Save: Invalid scope.");
    }

    context.deallocate_register(passed_reg);
}

void ArrayInitializer::InitializeGlobals(std::ostream &stream, Context &context, Global &global_specs) const
{
    for (auto initializer : dynamic_cast<NodeList *>(initializer_list_)->get_nodes())
    {
        if (initializer == nullptr)
        {
            continue;
        }
        dynamic_cast<Constant *>(initializer)->SaveValue(global_specs);
    }
}
