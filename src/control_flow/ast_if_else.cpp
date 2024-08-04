#include "../../include/control_flow/ast_if_else.hpp"

void IfElse::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    std::string end_label = context.create_label("if_end");
    std::string false_label = context.create_label("if_else");

    // jump label should be the end label if there is no false statement
    std::string jump_label = (false_statement_ == nullptr) ? end_label : false_label;

    // evaluate the condition
    dynamic_cast<ConditionEvaluation *>(condition_)->Evaluate(stream, context, passed_reg, jump_label, false);

    // body of true statement immeadiately follows evaluation, no need for jump
    true_statement_->EmitRISC(stream, context, passed_reg);

    // body of false statement if exists
    if (false_statement_ != nullptr)
    {
        // unconditional jump from true statement to end if false statement exists
        stream << "j " << end_label << std::endl;

        // emit body of false statement
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
