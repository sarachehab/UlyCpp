#ifndef AST_DIRECT_DECLARATOR_HPP
#define AST_DIRECT_DECLARATOR_HPP

#include "ast_node.hpp"
#include "primitives/ast_identifier.hpp"
#include "functions/ast_parameter_definition.hpp"
#include "arrays/ast_array_declarator.hpp"

class Declarator : public Node
{
private:
    Node *direct_declarator_;

public:
    Declarator(Node *direct_declarator) : direct_declarator_(direct_declarator) {};
    ~Declarator()
    {
        delete direct_declarator_;
    };

    std::string GetIdentifier() const;
    std::vector<Parameter> GetParameters(Context &context) const;
    int GetScopeOffset() const;
    void StoreParameters(std::ostream &stream, Context &context, std::string passed_reg) const;
    bool IsPointer() const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

class DirectDeclarator : public Node
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
    std::string GetIdentifier() const;

    /**
     * @brief Get the parameters of the function
     */
    std::vector<Parameter> GetParameters(Context &context) const;

    /**
     * @brief Get the offset needed to account for variable declarations
     */
    int GetScopeOffset() const;

    /**
     * @brief Store the parameters of the function from argument registers to the memory stack
     */
    void StoreParameters(std::ostream &stream, Context &context, std::string passed_reg) const;
};

#endif
