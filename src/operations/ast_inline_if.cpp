#include "../../include/operations/ast_inline_if.hpp"

void InlineIf::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    context.set_operation_type(GetType(context));
    if_else_->EmitRISC(stream, context, passed_reg);
    context.pop_operation_type();
}

void InlineIf::Print(std::ostream &stream) const
{
    stream << "(";
    condition_->Print(stream);
    stream << " ? ";
    true_statement_->Print(stream);
    stream << " : ";
    false_statement_->Print(stream);
    stream << ")";
}

Type InlineIf::GetType(Context &context) const
{
    Type left_type = dynamic_cast<Operand *>(true_statement_)->GetType(context);
    Type right_type = dynamic_cast<Operand *>(false_statement_)->GetType(context);
    return std::max(left_type, right_type);
}
