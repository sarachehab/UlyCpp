#ifndef AST_EXPRESSION_HPP
#define AST_EXPRESSION_HPP

#include "../ast_node.hpp"
#include "../operations/ast_operand.hpp"

class Expression : public Operand
{
protected:
    std::vector<Node *> nodes_;

public:
    Expression(Node *first_node) : nodes_({first_node}) {}

    ~Expression()
    {
        for (auto node : nodes_)
        {
            delete node;
        }
    }

    Type GetType(Context &context) const;
    void PushBack(Node *item);

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    virtual void Print(std::ostream &stream) const override;
};

class ExpressionList : public NodeList
{
public:
    using NodeList::NodeList;
    ~ExpressionList() = default;

    void GetArguments(std::ostream &stream, Context &context, std::string passed_reg) const;
    void Print(std::ostream &stream) const override;
};

#endif
