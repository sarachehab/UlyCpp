#include "../../include/enums/ast_enumerator.hpp"

std::string Enumerator::GetLabel() const
{
    return label_;
}

int Enumerator::DefineEnumerator(int value) const
{

    if (constant_expression_)
    {
        value = GetValue();
    }

    Context::define_enum_label_value_correspondance(label_, value);
    return value + 1;
}

void Enumerator::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    throw std::runtime_error("Enumerator::EmitRISC not implemented");
}

void Enumerator::Print(std::ostream &stream) const
{
    stream << label_;

    if (constant_expression_)
    {
        stream << " = ";
        constant_expression_->Print(stream);
    }

    stream << "," << std::endl;
}

int Enumerator::GetValue() const
{
    IntConstant *int_constant = dynamic_cast<IntConstant *>(constant_expression_);

    if (int_constant != nullptr)
    {
        return int_constant->GetValue();
    }

    throw std::runtime_error("Enumerator::IntConstant - constant_expression not recognised");
}
