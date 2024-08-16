#ifndef AST_FUNCTION_DEFINITION_HPP
#define AST_FUNCTION_DEFINITION_HPP

#include "../ast_node.hpp"
#include "../ast_direct_declarator.hpp"
#include "../ast_type_specifier.hpp"
#include "../statements/ast_statements.hpp"
#include "../ast_declarator.hpp"

class FunctionDefinition : public Node
{

private:
    Node *declaration_specifiers_;
    Node *declarator_;
    Node *compound_statement_;

public:
    FunctionDefinition(Node *declaration_specifiers,
                       Node *declarator,
                       Node *compound_statement) : declaration_specifiers_(declaration_specifiers),
                                                   declarator_(declarator),
                                                   compound_statement_(compound_statement) {};

    ~FunctionDefinition()
    {
        delete declaration_specifiers_;
        delete declarator_;
        delete compound_statement_;
    };

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;

    void Print(std::ostream &stream) const override;
};

#endif
