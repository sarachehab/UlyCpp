#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

#include "../ast_node.hpp"
#include "./ast_declaration.hpp"

class Statement : public NodeList
{
public:
    using NodeList::NodeList;
    virtual ~Statement() = default;

    virtual int GetScopeOffset(Context &context) const = 0;
};

class CompoundStatement : public Statement
{
public:
    using Statement::Statement;
    ~CompoundStatement() override = default;

    int GetScopeOffset(Context &context) const;
    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
};

class StatementList : public Statement
{
public:
    using Statement::Statement;
    ~StatementList() override = default;

    int GetScopeOffset(Context &context) const;
};

class DeclarationList : public Statement
{
public:
    using Statement::Statement;
    ~DeclarationList() override = default;

    int GetScopeOffset(Context &context) const;
};

#endif
