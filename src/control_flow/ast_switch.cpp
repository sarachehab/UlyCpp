#include "../../include/control_flow/ast_switch.hpp"

void SwitchStatement::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    std::string end_label = context.create_label("end_switch");
    context.save_end_label(end_label);

    // Get expression type
    Type type = dynamic_cast<Operand *>(expression_)->GetType(context);
    context.set_operation_type(type);
    std::string expression_register = context.get_register(type);

    // Evaluate expression
    expression_->EmitRISC(stream, context, expression_register);

    // Emit jump conditions
    dynamic_cast<Statement *>(case_block_)->EmitCaseJumpCondition(stream, context, expression_register);
    context.pop_operation_type();

    // Emit case blocks
    case_block_->EmitRISC(stream, context, passed_reg);

    stream << end_label << ":" << std::endl;
    context.pop_end_label();
}

void SwitchStatement::Print(std::ostream &stream) const
{
    stream << "switch ";
    expression_->Print(stream);
    stream << std::endl;
    case_block_->Print(stream);
}
