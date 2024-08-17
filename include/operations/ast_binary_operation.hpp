#ifndef BINARY_OPERATION_HPP
#define BINARY_OPERATION_HPP

#include "../ast_node.hpp"
#include "ast_operand.hpp"

/**
 * @brief Abstract class for binary operations
 */
class BinaryOperation : public Operand
{
protected:
    Node *left_;
    Node *right_;

public:
    BinaryOperation(Node *left, Node *right) : left_(left), right_(right) {};
    ~BinaryOperation()
    {
        delete left_;
        delete right_;
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

    /**
     * @brief Get the type of the operation
     *
     * @param context Context object
     * @return Type of the operation
     */
    Type GetType(Context &context) const override;

    bool IsPointerOperation(Context &context) const override;
    void AdjustPointerOperation(std::ostream &stream, Context &context, std::string passed_register, Node *node) const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
