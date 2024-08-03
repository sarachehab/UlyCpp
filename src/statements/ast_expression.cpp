#include "../../include/statements/ast_expression.hpp"

void ExpressionList::GetArguments(std::ostream &stream, Context &context, std::string passed_reg) const
{
    Function function = context.get_function_call();
    int int_arg_reg = 10, float_arg_reg = 42;
    int argument_register_number;

    for (auto arg_nb = 0; arg_nb < function.arguments.size(); arg_nb++)
    {

        switch (function.arguments[arg_nb].type)
        {
        case Type::_CHAR:
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
        dynamic_cast<Operand *>(nodes_[arg_nb])->EmitRISC(stream, context, argument_register_name);
    }
}

void ExpressionList::Print(std::ostream &stream) const
{
    for (auto node : nodes_)
    {
        node->Print(stream);
        stream << ", ";
    }
    stream << std::endl;
}
