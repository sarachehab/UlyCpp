#include "../../include/statements/ast_statements.hpp"

void CompoundStatement::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    context.create_new_scope();
    for (auto statement : nodes_)
    {
        statement->EmitRISC(stream, context, passed_reg);
    }
    context.pop_scope();
}
