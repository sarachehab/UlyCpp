#include "../../include/control_flow/ast_while_loop.hpp"

void WhileLoop::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    std::string loop_label = context.create_label("start_while");
    std::string end_label = context.create_label("end_while");
    context.save_start_label(loop_label);
    context.save_end_label(end_label);

    stream << loop_label << ":" << std::endl;
    dynamic_cast<ConditionEvaluation *>(condition_)->Evaluate(stream, context, passed_reg, end_label);
    statement_->EmitRISC(stream, context, passed_reg);
    stream << "j " << loop_label << std::endl;
    stream << end_label << ":" << std::endl;

    context.pop_start_label();
    context.pop_end_label();
}

void WhileLoop::Print(std::ostream &stream) const
{
    stream << "while (";
    condition_->Print(stream);
    stream << ")";
    statement_->Print(stream);
}
