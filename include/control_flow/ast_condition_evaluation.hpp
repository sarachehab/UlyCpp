#ifndef AST_CONDITIONAL_EVALUATION_HPP
#define AST_CONDITIONAL_EVALUATION_HPP

#include "../ast_node.hpp"
#include "../statements/ast_expression.hpp"
#include "ast_control_flow.hpp"

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

    void CheckCondition(std::ostream &stream, Context &context, std::string condition_evaluation_register, std::string jump_label, Type type, bool inversion) const;
    void Evaluate(std::ostream &stream, Context &context, std::string passed_reg, std::string jump_label, bool inversion) const;

    std::string GetMneumonic(bool inversion) const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
