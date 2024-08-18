#ifndef AST_STRING_LITERAL_HPP
#define AST_STRING_LITERAL_HPP

#include "../ast_node.hpp"
#include "../operations/ast_operand.hpp"

class StringLiteral : public Operand
{
private:
    std::string value_;

public:
    StringLiteral(std::string *value)
    {
        value_ = *value;
        delete value;
    }
    ~StringLiteral() {}

    Type GetType(Context &context) const override;
    bool IsPointerOperation(Context &context) const override;
    std::string GetString() const;

    void SaveValue(Context &context, Global &global_specs) const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
