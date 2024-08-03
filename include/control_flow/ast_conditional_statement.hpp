#ifndef AST_CONDITIONAL_STATEMENT_HPP
#define AST_CONDITIONAL_STATEMENT_HPP

#include "../ast_node.hpp"
#include "../statements/ast_expression.hpp"

class ConditionalStatement : public Node
{
private:
    Node *condition_;
    Node *true_statement_;
    Node *false_statement_;

public:
    ConditionalStatement(Node *condition, Node *true_statement) : condition_(condition), true_statement_(true_statement), false_statement_(nullptr) {}
    ConditionalStatement(Node *condition, Node *true_statement, Node *false_statement) : condition_(condition), true_statement_(true_statement), false_statement_(false_statement) {}

    ~ConditionalStatement()
    {
        delete condition_;
        delete true_statement_;
        delete false_statement_;
    }

    void CheckCondition(std::ostream &stream, Context &context, std::string condition_evaluation_register, std::string jump_label, Type type) const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
