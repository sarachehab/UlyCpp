#ifndef AST_BITWISE_OPERATION_HPP
#define AST_BITWISE_OPERATION_HPP

#include "ast_binary_operation.hpp"
#include "ast_unary_operation.hpp"

class InclusiveOr : public BinaryOperation
{
public:
    using BinaryOperation::BinaryOperation;
    ~InclusiveOr() {}

    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

class ExclusiveOr : public BinaryOperation
{
public:
    using BinaryOperation::BinaryOperation;
    ~ExclusiveOr() {}

    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

class BitwiseAnd : public BinaryOperation
{
public:
    using BinaryOperation::BinaryOperation;
    ~BitwiseAnd() {}

    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

class LeftShift : public BinaryOperation
{
public:
    using BinaryOperation::BinaryOperation;
    ~LeftShift() {}

    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

class RightShift : public BinaryOperation
{
public:
    using BinaryOperation::BinaryOperation;
    ~RightShift() {}

    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

class OneComplement : public UnaryOperation
{
public:
    using UnaryOperation::UnaryOperation;
    ~OneComplement() {}

    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

#endif
