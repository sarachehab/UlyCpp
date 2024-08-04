#include "../../include/statements/ast_expression.hpp"

Type Expression::GetType(Context &context) const
{
    return dynamic_cast<Operand *>(nodes_[0])->GetType(context);
}

void Expression::PushBack(Node *item)
{
    nodes_.push_back(item);
}

void Expression::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    for (auto node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->EmitRISC(stream, context, passed_reg);
    }
}

void Expression::Print(std::ostream &stream) const
{
    for (auto node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->Print(stream);
    }
}

void ExpressionList::GetArguments(std::ostream &stream, Context &context, std::string passed_reg) const
{
    Function function = context.get_function_call();
    int int_arg_reg = 10, float_arg_reg = 42;
    int argument_register_number;

    for (long unsigned int arg_nb = 0; arg_nb < function.arguments.size(); arg_nb++)
    {

        switch (function.arguments[arg_nb].type)
        {
        case Type::_CHAR:
        case Type::_SHORT:
        case Type::_UNSIGNED_INT:
        case Type::_INT:
            argument_register_number = int_arg_reg++;
            break;
        case Type::_FLOAT:
        case Type::_DOUBLE:
            argument_register_number = float_arg_reg++;
            break;
        default:
            throw std::runtime_error("ExpressionList GetArguments: Unknown type");
        }

        std::string argument_register_name = context.get_register_name(argument_register_number);
        context.set_operation_type(function.arguments[arg_nb].type);
        dynamic_cast<Operand *>(nodes_[arg_nb])->EmitRISC(stream, context, argument_register_name);
        context.pop_operation_type();
    }
}

void ExpressionList::Print(std::ostream &stream) const
{
    for (auto node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }

        node->Print(stream);
        stream << ", ";
    }
    stream << std::endl;
}
