#ifndef AST_DIRECT_DECLARATOR_HPP
#define AST_DIRECT_DECLARATOR_HPP

#include "ast_node.hpp"
#include "ast_declarator.hpp"
#include "primitives/ast_identifier.hpp"
#include "functions/ast_parameter_definition.hpp"
#include "arrays/ast_array_declarator.hpp"

class DirectDeclarator : public Declarator
{
private:
    Node *identifier_;
    Node *parameter_list_;

public:
    DirectDeclarator(Node *identifier) : identifier_(identifier), parameter_list_(nullptr) {};
    DirectDeclarator(Node *identifier, Node *parameter_list) : identifier_(identifier), parameter_list_(parameter_list) {};
    ~DirectDeclarator()
    {
        delete identifier_;
        delete parameter_list_;
    };

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;

    /**
     * @brief Get the identifier name
     */
    std::string GetIdentifier() const override;

    /**
     * @brief Get the parameters of the function
     */
    std::vector<Parameter> GetParameters(Context &context) const override;

    /**
     * @brief Get the offset needed to account for variable declarations
     */
    int GetScopeOffset() const override;

    /**
     * @brief Store the parameters of the function from argument registers to the memory stack
     */
    void StoreParameters(std::ostream &stream, Context &context, std::string passed_reg) const override;

    bool IsPointer() const override;
};

#endif
