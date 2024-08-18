#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <string>
#include <vector>

#include "arrays/ast_array_declarator.hpp"
#include "arrays/ast_array_initializer.hpp"

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
#include "operations/ast_inline_if.hpp"

#include "control_flow/ast_if_else.hpp"
#include "control_flow/ast_while_loop.hpp"
#include "control_flow/ast_condition_evaluation.hpp"
#include "control_flow/ast_for_loop.hpp"
#include "control_flow/ast_do_while.hpp"
#include "control_flow/ast_break.hpp"
#include "control_flow/ast_continue.hpp"
#include "control_flow/ast_flow_breaker.hpp"
#include "control_flow/ast_switch.hpp"
#include "control_flow/ast_case.hpp"

#include "pointers/ast_pointer_declarator.hpp"
#include "pointers/ast_address_of.hpp"
#include "pointers/ast_dereference.hpp"

#include "size_of/ast_size_of.hpp"

#include "chars/ast_char_literal.hpp"
#include "chars/ast_string_literal.hpp"

#include "ast_translation_unit.hpp"
#include "ast_direct_declarator.hpp"
#include "ast_type_specifier.hpp"
#include "ast_declarator.hpp"
#include "ast_node.hpp"

#include "context/context.hpp"

extern Node *ParseAST(std::string file_name);

#endif
