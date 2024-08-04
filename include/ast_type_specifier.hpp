#ifndef AST_TYPE_SPECIFIER
#define AST_TYPE_SPECIFIER

#include "ast_node.hpp"

class TypeSpecifier : public Node
{
private:
    Type type_;

public:
    TypeSpecifier(Type type) : type_(type) {};
    ~TypeSpecifier() {};

    /**
     * @brief Get the type of the specifier
     */
    Type GetType() const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
