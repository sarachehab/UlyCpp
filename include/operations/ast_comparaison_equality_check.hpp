#ifndef AST_EQUALITY_COMPARAISON_HPP
#define AST_EQUALITY_COMPARAISON_HPP

#include "../ast_node.hpp"
#include "ast_comparaison.hpp"

class EqualityCheck : public ComparaisonOperation
{
public:
    using ComparaisonOperation::ComparaisonOperation;
    ~EqualityCheck() {}

    virtual std::string GetOperation() const override;
    virtual std::string GetMneumonic(Type type) const override { return ""; };

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
};

#endif
