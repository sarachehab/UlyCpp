#ifndef AST_LOGICAL_OPERATION_HPP
#define AST_LOGICAL_OPERATION_HPP

#include "../ast_node.hpp"
#include "ast_binary_operation.hpp"
#include "ast_unary_operation.hpp"

class LogicalOperation : public BinaryOperation
{

public:
    using BinaryOperation::BinaryOperation;
    ~LogicalOperation() {}

    virtual std::string GetMneumonic(Type type) const override = 0;
    virtual std::string GetOperation() const override = 0;
};

class Negate : public UnaryOperation
{
public:
    using UnaryOperation::UnaryOperation;
    ~Negate() {}

    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

class Inverse : public UnaryOperation
{
public:
    using UnaryOperation::UnaryOperation;
    ~Inverse() {}

    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

class LogicalAnd : public LogicalOperation
{
public:
    using LogicalOperation::LogicalOperation;
    ~LogicalAnd() {}

    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

class LogicalOr : public LogicalOperation
{
public:
    using LogicalOperation::LogicalOperation;
    ~LogicalOr() {}

    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

#endif
