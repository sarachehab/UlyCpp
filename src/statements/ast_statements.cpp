#include "../../include/statements/ast_statements.hpp"

void CompoundStatement::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    context.create_new_scope();

    for (auto statement : nodes_)
    {
        if (statement == nullptr)
        {
            continue;
        }
        statement->EmitRISC(stream, context, passed_reg);
    }
    context.pop_scope();
}

int DeclarationList::GetScopeOffset(Context &context) const
{
    int offset = 0;
    for (auto node : nodes_)
    {
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
    for (auto node : nodes_)
    {
        Statement *statement = dynamic_cast<Statement *>(node);
        offset += statement->GetScopeOffset(context);
    }
    return offset;
}
