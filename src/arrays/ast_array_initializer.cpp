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

void ArrayInitializer::Save(std::ostream &stream, Context &context, int initial_offset, Type type) const
{
    int offset = initial_offset;
    std::string passed_reg = context.get_register(type);

    // Iterate through initializer list and save each element to the stack
    for (auto initializer : dynamic_cast<NodeList *>(initializer_list_)->get_nodes())
    {
        dynamic_cast<Operand *>(initializer)->EmitRISC(stream, context, passed_reg);
        stream << context.store_instruction(type) << " " << passed_reg << ", " << offset << "(sp)" << std::endl;

        // Increase offset to get next element in array
        offset += types_size.at(type);
    }

    context.deallocate_register(passed_reg);
}
