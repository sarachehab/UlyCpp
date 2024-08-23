#ifndef AST_SPECIFIER_HPP
#define AST_SPECIFIER_HPP

#include "ast_node.hpp"

class Specifier : public Node
{
public:
    Specifier() {};
    ~Specifier() {};

    /**
     * @brief Get the type of the specifier
     */
    virtual Type GetType() const = 0;

    virtual void DefineSpecifier(Context &context) const = 0;

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    virtual void Print(std::ostream &stream) const override = 0;
};

#endif
