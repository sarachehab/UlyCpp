#ifndef AST_CONDITIONAL_EVALUATION_HPP
#define AST_CONDITIONAL_EVALUATION_HPP

#include "../ast_node.hpp"
#include "../statements/ast_expression.hpp"
#include "ast_control_flow.hpp"

/**
 * @brief Represents a condition evaluation
 *
 * Represents a condition evaluation, such as an IF, ELSE, WHILE, DO_WHILE, FOR
 */
class ConditionEvaluation : public ControlFlow
{
private:
    Node *condition_;

public:
    ConditionEvaluation(Node *condition) : condition_(condition) {}

    ~ConditionEvaluation()
    {
        delete condition_;
    }

    /**
     * @brief Check the condition and emit jump statement.
     *
     * Inversion should be true when body does not immediately follow the condition.
     * This is the case in DO_WHILE.
     *
     * @param stream Output stream
     * @param context Context object
     * @param condition_evaluation_register Register to store the result of the condition evaluation
     * @param jump_label Label to jump to
     * @param type Type of the condition
     * @param inversion Invert the condition
     */
    void CheckCondition(std::ostream &stream, Context &context, std::string condition_evaluation_register, std::string jump_label, Type type, bool inversion) const;

    /**
     * @brief Evaluate the condition and emit jump statement
     *
     * @param stream Output stream
     * @param context Context object
     * @param passed_reg Register to pass to the next node
     * @param jump_label Label to jump to
     * @param inversion Invert the condition
     */
    void Evaluate(std::ostream &stream, Context &context, std::string passed_reg, std::string jump_label, bool inversion) const;

    /**
     * @brief Get the mneumonic for the condition.
     *
     * @param inversion Invert the condition
     * @return Mneumonic
     */
    std::string GetMneumonic(bool inversion) const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
