#include "../../include/chars/ast_char_literal.hpp"
#include "../../include/chars/ast_char_literal.hpp"

Type CharLiteral::GetType(Context &context) const
{
    return Type::_CHAR;
}

bool CharLiteral::IsPointerOperation(Context &context) const
{
    return false;
}

void CharLiteral::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    stream << "li " << passed_reg << ", " << int(character_) << std::endl;
}

void CharLiteral::Print(std::ostream &stream) const
{
    stream << character_;
}
