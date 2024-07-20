#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

#include "../ast_node.hpp"

class CompoundStatement : public NodeList
{
public:
    using NodeList::NodeList;
    ~CompoundStatement() = default;
    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
};

class StatementList : public NodeList
{
public:
    using NodeList::NodeList;
    ~StatementList() = default;
};

#endif
