#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <string>
#include <vector>

#include "functions/ast_function_definition.hpp"

#include "statements/ast_return.hpp"
#include "statements/ast_statements.hpp"

#include "primitives/ast_identifier.hpp"
#include "primitives/ast_constant.hpp"

#include "ast_direct_declarator.hpp"
#include "ast_type_specifier.hpp"
#include "ast_node.hpp"

#include "context/context.hpp"

extern Node *ParseAST(std::string file_name);

#endif
