#ifndef AST_ENUMERATOR_HPP
#define AST_ENUMERATOR_HPP

#include "../ast_node.hpp"
#include "../primitives/ast_identifier.hpp"
#include "../primitives/ast_constant.hpp"

class Enumerator : public Node
{
private:
    std::string label_;
    Node *constant_expression_;

public:
    Enumerator(std::string *label) : label_(*label), constant_expression_(nullptr) { delete label; }
    Enumerator(std::string *label, Node *constant_expression) : label_(*label), constant_expression_(constant_expression) { delete label; }

    ~Enumerator()
    {
        delete constant_expression_;
    }

    int DefineEnumerator(Context &context, int value) const;
    std::string GetLabel() const;

    int GetValue(Context &context) const;
    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
