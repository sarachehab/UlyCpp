#include "../../include/statements/ast_statements.hpp"

void CompoundStatement::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Create new scope to stop child scope from corrupting parent scope
    context.create_new_scope();

    // Iterate through statements within compound statement
    for (auto statement : nodes_)
    {
        if (statement == nullptr)
        {
            continue;
        }
        statement->EmitRISC(stream, context, passed_reg);
    }

    // Pop scope, go back to parent scope
    context.pop_scope();
}

int DeclarationList::GetScopeOffset(Context &context) const
{
    int offset = 0;

    // Iterate through declaration statements
    for (auto node : nodes_)
    {
        // Add up sizes of variables
        Declaration *declaration = dynamic_cast<Declaration *>(node);
        offset += declaration->GetScopeOffset(context);
    }

    return offset;
}

int StatementList::GetScopeOffset(Context &context) const
{
    return 0;
}

int CompoundStatement::GetScopeOffset(Context &context) const
{
    int offset = 0;

    // Iterate through statements within compound statement
    for (auto node : nodes_)
    {
        // Add up sizes of variables. These are non-null only within declaration blocks.
        Statement *statement = dynamic_cast<Statement *>(node);
        offset += statement->GetScopeOffset(context);
    }
    return offset;
}

void Statement::EmitCaseJumpCondition(std::ostream &stream, Context &context, std::string passed_register) const
{
    // Iterate through statements within compound statement
    for (auto node : nodes_)
    {
        Case *case_node = dynamic_cast<Case *>(node);
        Statement *statement_node = dynamic_cast<Statement *>(node);

        // Case node: emit jump conditions
        if (case_node != nullptr)
        {
            case_node->EmitCondition(stream, context, passed_register);
        }

        // Statement node: keep looking for case node within
        else if (statement_node != nullptr)
        {
            statement_node->EmitCaseJumpCondition(stream, context, passed_register);
        }
    }
}
