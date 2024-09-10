#ifndef AST_TYPEDEF_DEFINITION_HPP
#define AST_TYPEDEF_DEFINITION_HPP

#include "../ast_node.hpp"
#include "../specifiers/ast_specifier.hpp"
#include "../pointers/ast_address_of.hpp"
#include "../pointers/ast_pointer_declarator.hpp"

class TypedefDefinition : public Node
{
private:
    Node *declaration_specifier_;
    Type type;
    int initial_number_pointers = 0;
    std::string base_type;

public:
    TypedefDefinition(Node *declaration_specifier) : declaration_specifier_(declaration_specifier) { ExtractDeclarationSpecifier(); }
    ~TypedefDefinition() { delete declaration_specifier_; }

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;

    void DefineTypedef(NodeList *aliases);
    void ExtractDeclarationSpecifier();
};

#endif
