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

int IntConstant::GetValue() const
{
    return value_;
}

void FloatConstant::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    int label_number = context.declare_constant(value_);

    // load address of floating number representation
    std::string address_register = context.get_register(Type::_INT);
    stream << "lui " << address_register << ", %hi(.constant_representation_" << label_number << ")" << std::endl;

    // fetch value from specified address
    stream << context.load_instruction(Type::_FLOAT) << " " << passed_reg << ", %lo(.constant_representation_" << label_number << ")" << "(" << address_register << ")" << std::endl;

    // deallocate register
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

    // load address of floating number representation
    std::string address_register = context.get_register(Type::_INT);
    stream << "lui " << address_register << ", %hi(.constant_representation_" << label_number << ")" << std::endl;

    // fetch value from specified address
    stream << context.load_instruction(Type::_DOUBLE) << " " << passed_reg << ", %lo(.constant_representation_" << label_number << ")" << "(" << address_register << ")" << std::endl;

    // deallocate register
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

void IntConstant::SaveValue(Global &global_specs) const
{
    global_specs.push_lower(value_);
}

void FloatConstant::SaveValue(Global &global_specs) const
{
    FloatRepresentation representation;
    representation.float_representation = value_;
    int lower_int = representation.integer_representation;

    global_specs.push_lower(lower_int);
}

void DoubleConstant::SaveValue(Global &global_specs) const
{
    DoubleRepresentation representation;
    representation.double_representation = value_;
    int lower_int = representation.parts.lower;
    int upper_int = representation.parts.upper;

    global_specs.push_lower(lower_int);
    global_specs.push_upper(upper_int);
}

bool Constant::IsPointerOperation(Context &context) const
{
    return false;
}
