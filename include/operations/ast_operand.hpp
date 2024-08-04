#ifndef ast_operand_HPP
#define ast_operand_HPP

#include "../ast_node.hpp"

/**
 * @brief Abstract class for operands
 *
 * Defined to use GetType.
 * Should eventually be extended to support register spillage.
 */
class Operand : public Node
{
public:
    Operand() {}
    ~Operand() {}

    /**
     * @brief Get the type of the operand
     *
     * @param context Context object
     * @return Type of the operand
     */
    virtual Type GetType(Context &context) const = 0;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override = 0;
    void Print(std::ostream &stream) const override = 0;
};

#endif
