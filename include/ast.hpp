#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <string>
#include <vector>

#include "ast_node.hpp"
#include "context/context.hpp"

extern Node *ParseAST(std::string file_name);

#endif
