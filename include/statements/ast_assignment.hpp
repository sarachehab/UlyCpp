#ifndef AST_ASSIGNMENT_HPP
#define AST_ASSIGNMENT_HPP

#include "../ast_node.hpp"
#include "../primitives/ast_identifier.hpp"

class AssignmentList : public NodeList
{
public:
    using NodeList::NodeList;
    ~AssignmentList() {}
};

class Assignment : public Node
{
private:
    Node *unary_expression_;
    Node *expression_;

public:
    Assignment(Node *unary_expression, Node *expression) : unary_expression_(unary_expression), expression_(expression) {}
    ~Assignment()
    {
        delete unary_expression_;
        delete expression_;
    }

    std::string GetIdentifier() const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
