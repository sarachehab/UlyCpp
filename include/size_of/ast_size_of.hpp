#ifndef AST_SIZE_OF_HPP
#define AST_SIZE_OF_HPP

#include "../ast_node.hpp"
#include "../specifiers/ast_specifier.hpp"
#include "../operations/ast_operand.hpp"
#include "../primitives/ast_constant.hpp"

class SizeOf : public Operand
{
private:
    Node *unary_expression_;
    Node *constant_expression_;
    int pointer_;

public:
    SizeOf(Node *unary_expression) : unary_expression_(unary_expression), constant_expression_(nullptr), pointer_(0) {}
    SizeOf(Node *unary_expression, int pointer) : unary_expression_(unary_expression), constant_expression_(nullptr), pointer_(pointer) {}
    SizeOf(Node *unary_expression, Node *constant_expression) : unary_expression_(unary_expression), constant_expression_(constant_expression), pointer_(0) {}
    SizeOf(Node *unary_expression, int pointer, Node *constant_expression) : unary_expression_(unary_expression), constant_expression_(constant_expression), pointer_(pointer) {}

    ~SizeOf()
    {
        delete unary_expression_;
        if (constant_expression_)
        {
            delete constant_expression_;
        }
    };

    Type GetType(Context &context) const override;
    bool IsPointerOperation(Context &context) const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
