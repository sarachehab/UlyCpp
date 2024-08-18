#include "../../include/chars/ast_string_literal.hpp"

Type StringLiteral::GetType(Context &context) const
{
    return Type::_INT;
}

bool StringLiteral::IsPointerOperation(Context &context) const
{
    return true;
}

void StringLiteral::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    int index = context.define_string(value_);
    stream << "lui " << passed_reg << ", %hi(string_" << index << ")" << std::endl;
    stream << "addi " << passed_reg << ", " << passed_reg << ", %lo(string_" << index << ")" << std::endl;
}

void StringLiteral::Print(std::ostream &stream) const
{
    stream << "\"" << value_ << "\"";
}

std::string StringLiteral::GetString() const
{
    return value_;
}

void StringLiteral::SaveValue(Context &context, Global &global_specs) const
{
    int index = context.define_string(value_);
    std::string label = "string_" + std::to_string(index);

    global_specs.push_label(label);
}
