#ifndef AST_SIZE_OF_HPP
#define AST_SIZE_OF_HPP

#include "../ast_node.hpp"
#include "../specifiers/ast_specifier.hpp"
#include "../operations/ast_operand.hpp"

class SizeOf : public Operand
{
private:
    Node *unary_expression_;

public:
    SizeOf(Node *unary_expression) : unary_expression_(unary_expression) {}

    ~SizeOf()
    {
        delete unary_expression_;
    };

    Type GetType(Context &context) const override;
    bool IsPointerOperation(Context &context) const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
