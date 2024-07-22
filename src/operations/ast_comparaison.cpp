#include "../../include/operations/ast_comparaison.hpp"

Type ComparaisonOperation::GetType(Context &context) const
{
    return Type::_INT;
}
