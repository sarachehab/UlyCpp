#include "../../include/control_flow/ast_for_loop.hpp"

void ForLoop::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Generate a unique label for the loop
    std::string loop_label = context.create_label("for_begin");
    std::string iteration_label = context.create_label("for_iteration");
    std::string end_label = context.create_label("for_end");

    // Save labels for break and continue statements
    context.save_start_label(iteration_label);
    context.save_end_label(end_label);

    // Emit the initialization
    initialization_->EmitRISC(stream, context, passed_reg);

    // Evaluate condition
    stream << loop_label << ":" << std::endl;
    dynamic_cast<ConditionEvaluation *>(condition_)->Evaluate(stream, context, passed_reg, end_label, false);

    // Emit the body
    body_->EmitRISC(stream, context, passed_reg);

    // Emit the iteration
    stream << iteration_label << ":" << std::endl;
    if (iteration_ != nullptr)
    {
        iteration_->EmitRISC(stream, context, passed_reg);
    }

    // Jump back to the loop label
    stream << "j " << loop_label << std::endl;

    // Emit the end label
    stream << end_label << ":" << std::endl;

    context.pop_start_label();
    context.pop_end_label();
}

void ForLoop::Print(std::ostream &stream) const
{
    stream << "for (";
    initialization_->Print(stream);
    stream << "; ";
    condition_->Print(stream);
    stream << "; ";
    if (iteration_ != nullptr)
    {
        iteration_->Print(stream);
    }
    stream << ") ";
    body_->Print(stream);
}
