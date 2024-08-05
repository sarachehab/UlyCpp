#ifndef AST_TRANSLATION_UNIT_HPP
#define AST_TRANSLATION_UNIT_HPP

#include "ast_node.hpp"
#include "functions/ast_function_definition.hpp"

class TranslationUnit : public NodeList
{
public:
    using NodeList::NodeList;
    ~TranslationUnit() = default;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
};

#endif
