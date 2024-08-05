#ifndef AST_DECLARATION_HPP
#define AST_DECLARATION_HPP

#include "../ast_node.hpp"
#include "../ast_type_specifier.hpp"
#include "../primitives/ast_identifier.hpp"
#include "ast_assignment.hpp"
#include "../ast_direct_declarator.hpp"
#include "../arrays/ast_array_declarator.hpp"

class Declaration : public Node
{
private:
    Node *type_specifier_;
    Node *declarator_list_;

public:
    Declaration(Node *type_specifier, Node *declarator_list) : type_specifier_(type_specifier), declarator_list_(declarator_list) {}
    ~Declaration()
    {
        delete type_specifier_;
        delete declarator_list_;
    }

    /**
     * @brief Get offset needed to account for variable declarations
     *
     * Goes through all the declarations and adds up the size of each variable
     *
     * @param context Context of the program
     * @return Offset
     */
    int GetScopeOffset(Context &context) const;

    Type GetType() const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
