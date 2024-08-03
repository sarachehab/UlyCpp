#ifndef AST_EXPRESSION_HPP
#define AST_EXPRESSION_HPP

#include "../ast_node.hpp"
#include "../operations/ast_operand.hpp"

class ExpressionList : public NodeList
{
public:
    using NodeList::NodeList;
    ~ExpressionList() = default;

    void GetArguments(std::ostream &stream, Context &context, std::string passed_reg) const;
    void Print(std::ostream &stream) const override;
};

#endif
