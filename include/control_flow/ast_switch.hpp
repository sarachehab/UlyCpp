#ifndef AST_SWITCH_HPP
#define AST_SWITCH_HPP

#include "../ast_node.hpp"
#include "../statements/ast_statements.hpp"
#include "../operations/ast_operand.hpp"

class SwitchStatement : public Node
{
private:
    Node *expression_;
    Node *case_block_;

public:
    SwitchStatement(Node *expression, Node *case_block) : expression_(expression), case_block_(case_block) {}
    ~SwitchStatement()
    {
        delete expression_;
        delete case_block_;
    }

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
