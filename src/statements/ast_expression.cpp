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
    // Iterate through expressions
    for (auto node : nodes_)
    {
        // There to fix bug
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
    // Get function parameters list to get individual types of args
    Function function = context.get_function_call();
    int int_arg_reg = 10, float_arg_reg = 42;
    int argument_register_number;

    Type type;

    // Iterate through list of arguments
    for (long unsigned int arg_nb = 0; arg_nb < function.arguments.size(); arg_nb++)
    {

        type = function.arguments[arg_nb].is_pointer ? Type::_INT : function.arguments[arg_nb].type;

        switch (type)
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

        // Get argument register name
        std::string argument_register_name = context.get_register_name(argument_register_number);

        // Evaluate argument and store in register
        context.set_operation_type(type);
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

bool Expression::IsPointerOperation(Context &context) const
{
    return false;
}
