#ifndef AST_FUNCTION_CALL_HPP
#define AST_FUNCTION_CALL_HPP

#include "../ast_node.hpp"
#include "../primitives/ast_identifier.hpp"
#include "../statements/ast_assignment.hpp"
#include "../operations/ast_operand.hpp"

class FunctionCall : public Operand
{
private:
    Node *identifier_;
    Node *argument_list_;

public:
    FunctionCall(Node *identifier) : identifier_(identifier), argument_list_(nullptr) {};
    FunctionCall(Node *identifier, Node *argument_list) : identifier_(identifier), argument_list_(argument_list) {};

    ~FunctionCall()
    {
        delete identifier_;
        delete argument_list_;
    };

    Type GetType(Context &context) const override;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
