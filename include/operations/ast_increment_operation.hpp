#ifndef AST_INCREMENT_OPERATION_HPP
#define AST_INCREMENT_OPERATION_HPP

#include "../ast_node.hpp"
#include "../statements/ast_assignment.hpp"
#include "../primitives/ast_identifier.hpp"
#include "ast_binary_operation.hpp"
#include "ast_operand.hpp"

class IncrementOperation : public Operand
{
protected:
    Node *identifier_;
    Node *operation_;
    Node *assignment_;

public:
    IncrementOperation(Node *identifier, Node *operation) : identifier_(identifier), operation_(operation)
    {
        assignment_ = new Assignment(identifier_, operation);
    };
    virtual ~IncrementOperation()
    {
        delete assignment_; // operation_ and identifier_ are deleted in assignment_
    };

    virtual Type GetType(Context &context) const;

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override = 0;
    virtual void Print(std::ostream &stream) const override = 0;
};

class PostfixIncrement : public IncrementOperation
{
public:
    using IncrementOperation::IncrementOperation;
    ~PostfixIncrement(){};

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

class Prefixincrement : public IncrementOperation
{
public:
    using IncrementOperation::IncrementOperation;
    ~Prefixincrement(){};

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
