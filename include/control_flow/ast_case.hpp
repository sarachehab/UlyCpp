#ifndef AST_CASE_HPP
#define AST_CASE_HPP

#include "../ast_node.hpp"
#include "../operations/ast_operand.hpp"

class Case : public Node
{
protected:
    Node *expression_;
    Node *case_block_;
    std::string jump_label_;

public:
    Case(Node *case_block) : expression_(nullptr), case_block_(case_block)
    {
        jump_label_ = Context::create_label("default");
    }
    Case(Node *expression, Node *case_block) : expression_(expression), case_block_(case_block)
    {
        jump_label_ = Context::create_label("case");
    }
    ~Case()
    {
        delete expression_;
        delete case_block_;
    }

    /**
     * @brief Emit jump statements for the case
     */
    virtual void EmitCondition(std::ostream &stream, Context &context, std::string passed_register) const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

class DefaultCase : public Case
{
public:
    DefaultCase(Node *case_block) : Case(case_block) {}
    ~DefaultCase() = default;

    virtual void EmitCondition(std::ostream &stream, Context &context, std::string passed_register) const override;

    void Print(std::ostream &stream) const override;
};

#endif
