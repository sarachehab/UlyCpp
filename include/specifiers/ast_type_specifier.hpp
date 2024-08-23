#ifndef AST_TYPE_SPECIFIER_HPP
#define AST_TYPE_SPECIFIER_HPP

#include "../ast_node.hpp"
#include "ast_specifier.hpp"

class TypeSpecifier : public Specifier
{
private:
    Type type_;

public:
    TypeSpecifier(Type type) : type_(type) {};
    ~TypeSpecifier() {};

    void DefineSpecifier(Context &context) const override;

    /**
     * @brief Get the type of the specifier
     */
    Type GetType() const override;
    void Print(std::ostream &stream) const override;
};

#endif
