#ifndef AST_UNARY_OPERATION_HPP
#define AST_UNARY_OPERATION_HPP

#include "../ast_node.hpp"
#include "ast_operand.hpp"

/**
 * @brief Abstract class for unary operations
 */
class UnaryOperation : public Operand
{
protected:
    Node *expression_;

public:
    UnaryOperation(Node *expression) : expression_(expression) {};
    ~UnaryOperation()
    {
        delete expression_;
    };

    /**
     * @brief Get the mneumonic for the operation
     *
     * @param type Type of the operation
     * @return Mneumonic
     */
    virtual std::string GetMneumonic(Type type) const = 0;

    /**
     * @brief Get the operation
     *
     * @return Operation symbol
     */
    virtual std::string GetOperation() const = 0;

    Type GetType(Context &context) const override;

    bool IsPointerOperation(Context &context) const override;

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    virtual void Print(std::ostream &stream) const override;
};

#endif
