#include "../../include/control_flow/ast_do_while.hpp"

void DoWhileLoop::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Generate a unique label for the loop
    std::string loop_label = context.create_label("do_while_begin");
    std::string condition_label = context.create_label("do_while_condition");
    std::string end_label = context.create_label("do_while_end");

    // Save labels for break and continue statements
    context.save_start_label(condition_label);
    context.save_end_label(end_label);

    // Emit the body
    stream << loop_label << ":" << std::endl;
    body_->EmitRISC(stream, context, passed_reg);

    // Evaluate condition
    stream << condition_label << ":" << std::endl;
    dynamic_cast<ConditionEvaluation *>(condition_)->Evaluate(stream, context, passed_reg, loop_label, true);

    // Emit the end label
    stream << end_label << ":" << std::endl;

    context.pop_start_label();
    context.pop_end_label();
}

void DoWhileLoop::Print(std::ostream &stream) const
{
    stream << "do ";
    body_->Print(stream);
    stream << " while (";
    condition_->Print(stream);
    stream << ");";
}
