#include "../../include/statements/ast_assignment.hpp"

void Assignment::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    Variable variable_specs = context.get_variable(GetIdentifier());
    Type type = variable_specs.type;
    int offset = variable_specs.offset;
    context.set_operation_type(type);

    std::string reg = context.get_register(type);
    expression_->EmitRISC(stream, context, reg);

    stream << context.store_instruction(type) << " " << reg << ", " << offset << "(sp)" << std::endl;
    context.deallocate_register(reg);
    context.pop_operation_type();
}

void Assignment::Print(std::ostream &stream) const
{
    unary_expression_->Print(stream);
    stream << " = ";
    expression_->Print(stream);
    stream << ";" << std::endl;
}

std::string Assignment::GetIdentifier() const
{
    Identifier *identifier = dynamic_cast<Identifier *>(unary_expression_);
    if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    throw std::runtime_error("Assignment GetIdentifier: Not an identifier");
}

void Assignment::GetArgument(std::ostream &stream, Context &context, std::string passed_reg)
{
    int int_register = 10, float_register = 42;
    std::string arg_register;

    Function function = context.get_function_call();
    for (auto arg : function.arguments)
    {

        switch (arg.type)
        {
        case Type::_CHAR:
        case Type::_SHORT:
        case Type::_UNSIGNED_INT:
        case Type::_INT:
            arg_register = context.get_register_name(int_register++);
            break;
        case Type::_FLOAT:
        case Type::_DOUBLE:
            arg_register = context.get_register_name(float_register++);
            break;
        default:
            throw std::runtime_error("Assignment EmitRISC: Unknown argument type");
        }

        expression_->EmitRISC(stream, context, arg_register);
    }
    throw std::runtime_error("Assignment EmitRISC: Cannot assign in function call");
}

void AssignmentList::GetArguments(std::ostream &stream, Context &context, std::string passed_reg) const
{
    for (auto node : nodes_)
    {
        dynamic_cast<Assignment *>(node)->GetArgument(stream, context, passed_reg);
    }
}
