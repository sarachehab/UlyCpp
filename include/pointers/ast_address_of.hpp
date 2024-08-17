#ifndef AST_ADDRESS_OF_HPP
#define AST_ADDRESS_OF_HPP

#include "../ast_node.hpp"
#include "../operations/ast_unary_operation.hpp"
#include "../primitives/ast_identifier.hpp"
#include "../arrays/ast_array_access.hpp"

class AddressOf : public UnaryOperation
{
public:
    using UnaryOperation::UnaryOperation;
    ~AddressOf() = default;

    std::string GetMneumonic(Type type) const;
    std::string GetOperation() const;
    bool IsPointerOperation(Context &context) const override;

    std::string GetIdentifier() const;
    Type GetType(Context &context) const override;
    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
};

#endif
