#include "../../include/size_of/ast_size_of.hpp"

Type SizeOf::GetType(Context &context) const
{
    return Type::_INT;
}

bool SizeOf::IsPointerOperation(Context &context) const
{
    return false;
}

void SizeOf::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    Specifier *type_specifier = dynamic_cast<Specifier *>(unary_expression_);
    Operand *operand = dynamic_cast<Operand *>(unary_expression_);

    Type type;

    if (type_specifier != nullptr)
    {
        type = type_specifier->GetType();

        if (pointer_ > 0)
        {
            type = Type::_INT;
        }
    }
    else if (operand != nullptr)
    {
        type = operand->IsPointerOperation(context) ? Type::_INT : operand->GetType(context);
    }
    else
    {
        throw std::runtime_error("SizeOf: unary_expression_ is not a TypeSpecifier or Operand");
    }

    int size = types_size.at(type);

    if (constant_expression_)
    {
        size *= dynamic_cast<IntConstant *>(constant_expression_)->GetValue();
    }

    stream << "li " << passed_reg << ", " << size << std::endl;
}

void SizeOf::Print(std::ostream &stream) const
{
    stream << "SizeOf(";
    unary_expression_->Print(stream);

    for (int i = 0; i < pointer_; i++)
    {
        stream << "*";
    }

    if (constant_expression_)
    {
        stream << "[";
        constant_expression_->Print(stream);
        stream << "]";
    }
    stream << ")";
}
