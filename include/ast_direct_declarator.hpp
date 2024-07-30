#ifndef AST_DIRECT_DECLARATOR_HPP
#define AST_DIRECT_DECLARATOR_HPP

#include "ast_node.hpp"
#include "primitives/ast_identifier.hpp"
#include "functions/ast_parameter_definition.hpp"

class DirectDeclarator : public Node
{
private:
    Node *identifier_;
    Node *parameter_list_;

public:
    DirectDeclarator(Node *identifier) : identifier_(identifier), parameter_list_(nullptr){};
    DirectDeclarator(Node *identifier, Node *parameter_list) : identifier_(identifier), parameter_list_(parameter_list){};
    ~DirectDeclarator()
    {
        delete identifier_;
        delete parameter_list_;
    };

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;

    std::string GetIdentifier() const;
    std::vector<Parameter> GetParameters(Context &context) const;
    int GetScopeOffset() const;
    void StoreParameters(std::ostream &stream, Context &context, std::string passed_reg) const;
};

#endif
