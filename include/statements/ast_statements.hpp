#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

#include "../ast_node.hpp"
#include "./ast_declaration.hpp"
#include "../control_flow/ast_case.hpp"

class Statement : public NodeList
{
public:
    using NodeList::NodeList;
    virtual ~Statement() = default;

    /**
     * @brief Get the offset of the scope
     *
     * Determines the offset needed for declarations in the scope.
     * Goes through all declarations and adds up sizes of variables.
     * Should be later extended to account for register spillage.
     *
     * @param context Context
     * @return Offset of the scope
     */
    virtual int GetScopeOffset(Context &context) const = 0;

    /**
     * @brief Emit RISC-V code for the case statements
     */
    virtual void EmitCaseJumpCondition(std::ostream &stream, Context &context, std::string passed_register) const;
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
