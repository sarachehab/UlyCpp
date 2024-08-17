#ifndef AST_DEREFERENCE_HPP
#define AST_DEREFERENCE_HPP

#include "ast_node.hpp"
#include "../operations/ast_unary_operation.hpp"
#include "../arrays/ast_array_access.hpp"
#include "../primitives/ast_identifier.hpp"

class Dereference : public UnaryOperation
{
public:
    using UnaryOperation::UnaryOperation;
    ~Dereference() override = default;

    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;

    std::string GetIdentifier() const;
    Type GetType(Context &context) const override;
    bool IsPointer(Context &context) const;

    int PointerDereferenceCount() const;
    bool IsPointerOperation(Context &context) const override;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void InitialOffset(std::ostream &stream, Context &context, std::string address_reg) const;
    void ExecutePathDereference(std::ostream &stream, Context &context, std::string address_register) const;
};

#endif
