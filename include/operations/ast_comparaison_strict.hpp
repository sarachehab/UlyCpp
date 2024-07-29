#ifndef AST_STRICT_COMPARAISON_HPP
#define AST_STRICT_COMPARAISON_HPP

#include "../ast_node.hpp"
#include "ast_comparaison.hpp"
#include "ast_operand.hpp"

class StrictComparaisonOperation : public ComparaisonOperation
{
public:
    using ComparaisonOperation::ComparaisonOperation;
    ~StrictComparaisonOperation() {}

    virtual std::string GetMneumonic(Type type) const override = 0;
    virtual std::string GetOperation() const override = 0;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
};

class LessThan : public StrictComparaisonOperation
{
public:
    using StrictComparaisonOperation::StrictComparaisonOperation;
    ~LessThan() {}

    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

#endif
