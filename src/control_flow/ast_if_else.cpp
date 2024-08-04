#include "../../include/control_flow/ast_if_else.hpp"

void IfElse::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    std::string end_label = context.create_label("if_end");
    std::string false_label = context.create_label("if_else");
    std::string jump_label = (false_statement_ == nullptr) ? end_label : false_label;

    dynamic_cast<ConditionEvaluation *>(condition_)->Evaluate(stream, context, passed_reg, jump_label, false);

    true_statement_->EmitRISC(stream, context, passed_reg);

    if (false_statement_ != nullptr)
    {
        stream << "j " << end_label << std::endl;
        stream << false_label << ":" << std::endl;
        false_statement_->EmitRISC(stream, context, passed_reg);
    }

    stream << end_label << ":" << std::endl;
}

void IfElse::Print(std::ostream &stream) const
{
    stream << "if (";
    condition_->Print(stream);
    stream << ")" << std::endl;
    true_statement_->Print(stream);

    if (false_statement_ != nullptr)
    {
        stream << "else" << std::endl;
        false_statement_->Print(stream);
    }
}
