#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <string>
#include <vector>

#include "functions/ast_parameter_definition.hpp"
#include "functions/ast_function_definition.hpp"
#include "functions/ast_function_call.hpp"

#include "statements/ast_assignment.hpp"
#include "statements/ast_declaration.hpp"
#include "statements/ast_return.hpp"
#include "statements/ast_statements.hpp"
#include "statements/ast_expression.hpp"

#include "primitives/ast_constant.hpp"
#include "primitives/ast_identifier.hpp"

#include "operations/ast_arithmetic_operation.hpp"
#include "operations/ast_binary_operation.hpp"
#include "operations/ast_bitwise_operation.hpp"
#include "operations/ast_comparaison_strict.hpp"
#include "operations/ast_comparaison_equality_check.hpp"
#include "operations/ast_increment_operation.hpp"
#include "operations/ast_logical_operation.hpp"
#include "operations/ast_unary_operation.hpp"

#include "ast_direct_declarator.hpp"
#include "ast_type_specifier.hpp"
#include "ast_node.hpp"

#include "context/context.hpp"

extern Node *ParseAST(std::string file_name);

#endif
