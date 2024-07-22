#ifndef BINARY_OPERATION_HPP
#define BINARY_OPERATION_HPP

#include "../ast_node.hpp"
#include "ast_operand.hpp"

class BinaryOperation : public Operand
{
protected:
    Node *left_;
    Node *right_;

public:
    BinaryOperation(Node *left, Node *right) : left_(left), right_(right){};
    ~BinaryOperation()
    {
        delete left_;
        delete right_;
    };

    virtual std::string GetMneumonic(Type type) const = 0;
    virtual std::string GetOperation() const = 0;

    Type GetType(Context &context) const override;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
