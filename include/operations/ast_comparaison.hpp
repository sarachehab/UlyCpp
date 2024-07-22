#ifndef AST_COMPARAISON_HPP
#define AST_COMPARAISON_HPP

#include "../ast_node.hpp"
#include "ast_binary_operation.hpp"

class ComparaisonOperation : public BinaryOperation
{
public:
    using BinaryOperation::BinaryOperation;
    ~ComparaisonOperation() {}

    virtual std::string GetOperation() const = 0;
    virtual Type GetType(Context &context) const override;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override = 0;
};

#endif
