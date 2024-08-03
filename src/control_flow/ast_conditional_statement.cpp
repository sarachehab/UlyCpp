#include "../../include/control_flow/ast_conditional_statement.hpp"

void ConditionalStatement::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    std::string end_label = context.create_label("if_end");
    std::string false_label = context.create_label("if_else");
    std::string jump_label = (false_statement_ == nullptr) ? end_label : false_label;

    Type type = dynamic_cast<Expression *>(condition_)->GetType(context);
    std::string condition_evaluation_register = context.get_register(type);

    condition_->EmitRISC(stream, context, condition_evaluation_register);
    CheckCondition(stream, context, condition_evaluation_register, jump_label, type);
    context.deallocate_register(condition_evaluation_register);

    true_statement_->EmitRISC(stream, context, passed_reg);

    if (false_statement_ != nullptr)
    {
        stream << false_label << ":" << std::endl;
        false_statement_->EmitRISC(stream, context, passed_reg);
    }

    stream << end_label << ":" << std::endl;
}

void ConditionalStatement::CheckCondition(std::ostream &stream, Context &context, std::string condition_evaluation_register, std::string jump_label, Type type) const
{

    std::string float_zero_register, double_zero_register, temporary_register;

    switch (type)
    {
    case Type::_CHAR:
    case Type::_UNSIGNED_INT:
    case Type::_SHORT:
    case Type::_INT:
        stream << "beqz " << condition_evaluation_register << ", " << jump_label << std::endl;
        break;

    case Type::_FLOAT:
        float_zero_register = context.get_register(Type::_FLOAT);
        temporary_register = context.get_register(Type::_INT);
        stream << "fmv.s.x " << float_zero_register << ", zero" << std::endl;
        stream << "feq.s " << temporary_register << ", " << condition_evaluation_register << ", " << float_zero_register << std::endl;
        stream << "beqz " << temporary_register << ", " << jump_label << std::endl;
        context.deallocate_register(float_zero_register);
        context.deallocate_register(temporary_register);
        break;

    case Type::_DOUBLE:
        double_zero_register = context.get_register(Type::_DOUBLE);
        temporary_register = context.get_register(Type::_INT);
        stream << "fcvt.d.w " << double_zero_register << ", zero" << std::endl;
        stream << "feq.d " << temporary_register << ", " << condition_evaluation_register << ", " << double_zero_register << std::endl;
        stream << "beqz " << temporary_register << ", " << jump_label << std::endl;
        context.deallocate_register(double_zero_register);
        context.deallocate_register(temporary_register);
        break;

    default:
        throw std::runtime_error("ConditionalStatement CheckCondition: Invalid type");
    }
}

void ConditionalStatement::Print(std::ostream &stream) const
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
