#ifndef AST_DIRECT_DECLARATOR_HPP
#define AST_DIRECT_DECLARATOR_HPP

#include "ast_node.hpp"
#include "primitives/ast_identifier.hpp"

class DirectDeclarator : public Node
{
private:
    Node *identifier_;

public:
    DirectDeclarator(Node *identifier) : identifier_(identifier){};
    ~DirectDeclarator() { delete identifier_; };

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;

    std::string GetIdentifier() const;
};

#endif
