#ifndef AST_CONDITIONAL_EVALUATION_HPP
#define AST_CONDITIONAL_EVALUATION_HPP

#include "../ast_node.hpp"
#include "../statements/ast_expression.hpp"

class ConditionEvaluation : public Node
{
private:
    Node *condition_;

public:
    ConditionEvaluation(Node *condition) : condition_(condition) {}

    ~ConditionEvaluation()
    {
        delete condition_;
    }

    void CheckCondition(std::ostream &stream, Context &context, std::string condition_evaluation_register, std::string jump_label, Type type) const;
    void Evaluate(std::ostream &stream, Context &context, std::string passed_reg, std::string jump_label) const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
