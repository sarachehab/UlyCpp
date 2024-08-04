#include "../../include/control_flow/ast_condition_evaluation.hpp"

void ConditionEvaluation::CheckCondition(std::ostream &stream, Context &context, std::string condition_evaluation_register, std::string jump_label, Type type, bool inversion) const
{
    std::string float_zero_register, double_zero_register, temporary_register;

    switch (type)
    {
    case Type::_CHAR:
    case Type::_UNSIGNED_INT:
    case Type::_SHORT:
    case Type::_INT:
        break;

    case Type::_FLOAT:
        float_zero_register = context.get_register(Type::_FLOAT);
        temporary_register = context.get_register(Type::_INT);
        stream << "fmv.s.x " << float_zero_register << ", zero" << std::endl;
        stream << "feq.s " << temporary_register << ", " << condition_evaluation_register << ", " << float_zero_register << std::endl;
        context.deallocate_register(float_zero_register);
        context.deallocate_register(temporary_register);
        break;

    case Type::_DOUBLE:
        double_zero_register = context.get_register(Type::_DOUBLE);
        temporary_register = context.get_register(Type::_INT);
        stream << "fcvt.d.w " << double_zero_register << ", zero" << std::endl;
        stream << "feq.d " << temporary_register << ", " << condition_evaluation_register << ", " << double_zero_register << std::endl;
        context.deallocate_register(double_zero_register);
        context.deallocate_register(temporary_register);
        break;

    default:
        throw std::runtime_error("ConditionalStatement CheckCondition: Invalid type");
    }

    stream << GetMneumonic(inversion) << " " << condition_evaluation_register << ", " << jump_label << std::endl;
}

void ConditionEvaluation::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // this is never called
}

void ConditionEvaluation::Evaluate(std::ostream &stream, Context &context, std::string passed_reg, std::string jump_label, bool inversion) const
{
    Type type = dynamic_cast<Expression *>(condition_)->GetType(context);
    std::string condition_evaluation_register = context.get_register(type);

    condition_->EmitRISC(stream, context, condition_evaluation_register);

    CheckCondition(stream, context, condition_evaluation_register, jump_label, type, inversion);

    context.deallocate_register(condition_evaluation_register);
}

void ConditionEvaluation::Print(std::ostream &stream) const
{
    condition_->Print(stream);
}

std::string ConditionEvaluation::GetMneumonic(bool inversion) const
{
    return inversion ? "bnez" : "beqz";
}
