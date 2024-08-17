#ifndef AST_ARRAY_DECLARATOR_HPP
#define AST_ARRAY_DECLARATOR_HPP

#include "../ast_node.hpp"
#include "../primitives/ast_constant.hpp"
#include "../primitives/ast_identifier.hpp"
#include "../pointers/ast_pointer_declarator.hpp"
#include "../ast_declarator.hpp"

class ArrayDeclarator : public Declarator
{
private:
    Node *identifier_;
    Node *constant_expression_;

public:
    ArrayDeclarator(Node *identifier, Node *constant_expression) : identifier_(identifier), constant_expression_(constant_expression) {}
    ArrayDeclarator(Node *identifier) : identifier_(identifier), constant_expression_(nullptr) {}

    ~ArrayDeclarator()
    {
        delete identifier_;
        delete constant_expression_;
    }

    std::string GetIdentifier() const override;

    /**
     * @brief Get the size of the array
     */
    int GetSize() const;
    bool IsPointer() const override;

    virtual std::vector<Parameter> GetParameters(Context &context) const override;
    virtual int GetScopeOffset() const override;
    virtual void StoreParameters(std::ostream &stream, Context &context, std::string passed_reg) const override;

    int GetDereferenceNumber() const override;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const;
    void Print(std::ostream &stream) const;
};

#endif
