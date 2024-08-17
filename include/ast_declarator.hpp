#ifndef AST_DECLARATOR_HPP
#define AST_DECLARATOR_HPP

#include "ast_node.hpp"

class Declarator : public Node
{
public:
    virtual std::string GetIdentifier() const = 0;
    virtual std::vector<Parameter> GetParameters(Context &context) const = 0;
    virtual int GetScopeOffset() const = 0;
    virtual void StoreParameters(std::ostream &stream, Context &context, std::string passed_reg) const = 0;
    virtual bool IsPointer() const = 0;
    virtual int GetDereferenceNumber() const = 0;

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override = 0;
    virtual void Print(std::ostream &stream) const override = 0;
};

#endif
