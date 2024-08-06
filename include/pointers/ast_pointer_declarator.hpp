#ifndef AST_POINTER_DECLARATOR_HPP
#define AST_POINTER_DECLARATOR_HPP

#include "../ast_node.hpp"
#include "../primitives/ast_identifier.hpp"

class PointerDeclarator : public Node
{
private:
    Node *direct_declarator_;

public:
    PointerDeclarator(Node *direct_declarator) : direct_declarator_(direct_declarator) {}

    ~PointerDeclarator()
    {
        delete direct_declarator_;
    }

    std::string GetIdentifier() const;
    Type GetType() const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_register) const override;
    void Print(std::ostream &stream) const override;
};

#endif
