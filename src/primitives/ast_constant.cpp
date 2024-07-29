#include "../../include/primitives/ast_constant.hpp"

void IntConstant::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    stream << "li " << passed_reg << ", " << value_ << std::endl;
}

void IntConstant::Print(std::ostream &stream) const
{
    stream << value_;
}

Type IntConstant::GetType(Context &context) const
{
    return Type::_INT;
}

void FloatConstant::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    int label_number = context.declare_constant(value_);

    std::string address_register = context.get_register(Type::_INT);
    stream << "lui " << address_register << ", %hi(.constant_representation_" << label_number << ")" << std::endl;
    stream << context.load_instruction(Type::_FLOAT) << " " << passed_reg << ", %lo(.constant_representation_" << label_number << ")" << "(" << address_register << ")" << std::endl;
    context.deallocate_register(address_register);
}

void FloatConstant::Print(std::ostream &stream) const
{
    stream << value_;
}

Type FloatConstant::GetType(Context &context) const
{
    return Type::_FLOAT;
}

void DoubleConstant::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    int label_number = context.declare_constant(value_);

    std::string address_register = context.get_register(Type::_INT);
    stream << "lui " << address_register << ", %hi(.constant_representation_" << label_number << ")" << std::endl;
    stream << context.load_instruction(Type::_DOUBLE) << " " << passed_reg << ", %lo(.constant_representation_" << label_number << ")" << "(" << address_register << ")" << std::endl;
    context.deallocate_register(address_register);
}

void DoubleConstant::Print(std::ostream &stream) const
{
    stream << value_;
}

Type DoubleConstant::GetType(Context &context) const
{
    return Type::_DOUBLE;
}
