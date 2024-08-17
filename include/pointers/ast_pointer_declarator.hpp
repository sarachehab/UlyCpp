#ifndef AST_POINTER_DECLARATOR_HPP
#define AST_POINTER_DECLARATOR_HPP

#include "../ast_node.hpp"
#include "../primitives/ast_identifier.hpp"
#include "../ast_direct_declarator.hpp"
#include "../ast_declarator.hpp"

class PointerDeclarator : public Declarator
{
private:
    Node *direct_declarator_;

public:
    PointerDeclarator(Node *direct_declarator) : direct_declarator_(direct_declarator) {}

    ~PointerDeclarator()
    {
        delete direct_declarator_;
    }

    std::string GetIdentifier() const override;
    Type GetType() const;

    int GetDereferenceNumber() const override;

    virtual std::vector<Parameter> GetParameters(Context &context) const override;
    virtual int GetScopeOffset() const override;
    virtual void StoreParameters(std::ostream &stream, Context &context, std::string passed_reg) const override;
    virtual bool IsPointer() const override;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_register) const override;
    void Print(std::ostream &stream) const override;
};

#endif
