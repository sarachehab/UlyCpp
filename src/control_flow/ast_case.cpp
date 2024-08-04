#include "../../include/control_flow/ast_case.hpp"

void Case::EmitCondition(std::ostream &stream, Context &context, std::string passed_register) const
{
    Type type = std::max(dynamic_cast<Operand *>(expression_)->GetType(context), context.get_operation_type());

    // Evaluate the expression
    std::string comparaison_register_ = context.get_register(type);
    expression_->EmitRISC(stream, context, comparaison_register_);

    // Compare the expression with the passed register
    stream << "beq " << passed_register << ", " << comparaison_register_ << ", " << jump_label_ << std::endl;
    context.deallocate_register(comparaison_register_);
}

void Case::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    stream << jump_label_ << ":" << std::endl;

    // Emit case body
    case_block_->EmitRISC(stream, context, passed_reg);
}

void Case::Print(std::ostream &stream) const
{
    stream << "case ";
    expression_->Print(stream);
    stream << ": ";
    case_block_->Print(stream);
}

void DefaultCase::EmitCondition(std::ostream &stream, Context &context, std::string passed_register) const
{
    // Always jump to the default case
    stream << "j " << jump_label_ << std::endl;
}

void DefaultCase::Print(std::ostream &stream) const
{
    stream << "default: ";
    case_block_->Print(stream);
}
