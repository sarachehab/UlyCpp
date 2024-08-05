#include "../include/ast_translation_unit.hpp"

void TranslationUnit::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    stream << ".text" << std::endl;
    for (auto &node : nodes_)
    {

        if (node == nullptr)
        {
            continue;
        }

        FunctionDefinition *function_definition = dynamic_cast<FunctionDefinition *>(node);
        Declaration *declaration = dynamic_cast<Declaration *>(node);

        if (function_definition != nullptr)
        {
            function_definition->EmitRISC(stream, context, passed_reg);
        }

        else if (declaration != nullptr)
        {
            declaration->DeclareGlobal(stream, context, passed_reg);
        }
    }
}
