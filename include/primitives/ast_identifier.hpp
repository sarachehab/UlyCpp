#ifndef AST_IDENTIFIER_HPP
#define AST_IDENTIFIER_HPP

#include "../ast_node.hpp"
#include "../operations/ast_operand.hpp"

class Identifier : public Operand
{
private:
    std::string identifier_;

public:
    Identifier(std::string *identifier) : identifier_(*identifier) { delete identifier; };
    ~Identifier() {};

    Type GetType(Context &context) const override;
    bool IsPointerOperation(Context &context) const override;
    int GetValue(Context &context) const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;

    /**
     * @brief Get the identifier name
     * @return Identifier name
     */
    std::string GetIdentifier() const;
};

#endif
