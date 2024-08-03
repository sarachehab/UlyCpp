#ifndef AST_EXPRESSION_HPP
#define AST_EXPRESSION_HPP

#include "../ast_node.hpp"
#include "../operations/ast_operand.hpp"

class Expression : public NodeList
{
public:
    using NodeList::NodeList;
    ~Expression() = default;

    Type GetType(Context &context) const;
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
