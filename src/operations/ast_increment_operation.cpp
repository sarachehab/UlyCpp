#include "../../include/operations/ast_increment_operation.hpp"

Type IncrementOperation::GetType(Context &context) const
{
    return dynamic_cast<Operand *>(identifier_)->GetType(context);
}

void PostfixIncrement::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    identifier_->EmitRISC(stream, context, passed_reg);
    assignment_->EmitRISC(stream, context, passed_reg);
}

void PostfixIncrement::Print(std::ostream &stream) const
{
    identifier_->Print(stream);
    if (dynamic_cast<BinaryOperation *>(operation_)->GetOperation() == " + ")
    {
        stream << " ++ ";
    }
    else
    {
        stream << " -- ";
    }
}

void Prefixincrement::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    assignment_->EmitRISC(stream, context, passed_reg);
    identifier_->EmitRISC(stream, context, passed_reg);
}

void Prefixincrement::Print(std::ostream &stream) const
{
    if (dynamic_cast<BinaryOperation *>(operation_)->GetOperation() == " +")
    {
        stream << " ++ ";
    }
    else
    {
        stream << " -- ";
    }
    identifier_->Print(stream);
}
