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
    TypeSpecifier *type_specifier = dynamic_cast<TypeSpecifier *>(unary_expression_);
    Operand *operand = dynamic_cast<Operand *>(unary_expression_);

    Type type;

    if (type_specifier != nullptr)
    {
        type = type_specifier->GetType();
    }
    else if (operand != nullptr)
    {
        type = operand->IsPointerOperation(context) ? Type::_INT : operand->GetType(context);
    }
    else
    {
        throw std::runtime_error("SizeOf: unary_expression_ is not a TypeSpecifier or Operand");
    }

    stream << "li " << passed_reg << ", " << types_size.at(type) << std::endl;
}

void SizeOf::Print(std::ostream &stream) const
{
    stream << "SizeOf(";
    unary_expression_->Print(stream);
    stream << ")";
}
