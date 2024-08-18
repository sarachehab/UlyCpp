#ifndef AST_CHAR_LITERAL_HPP
#define AST_CHAR_LITERAL_HPP

#include "../ast_node.hpp"
#include "../operations/ast_operand.hpp"

class CharLiteral : public Operand
{
private:
    char character_;

public:
    CharLiteral(char character) : character_(character) {}
    ~CharLiteral() {}

    Type GetType(Context &context) const override;
    bool IsPointerOperation(Context &context) const override;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
