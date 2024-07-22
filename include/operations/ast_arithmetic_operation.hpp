#ifndef AST_ARITHMETIC_OPERATION_HPP
#define AST_ARITHMETIC_OPERATION_HPP

#include "ast_binary_operation.hpp"

class Addition : public BinaryOperation
{
public:
    using BinaryOperation::BinaryOperation;
    ~Addition() {}
    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

class Substraction : public BinaryOperation
{
public:
    using BinaryOperation::BinaryOperation;
    ~Substraction() {}
    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

class Multiplication : public BinaryOperation
{
public:
    using BinaryOperation::BinaryOperation;
    ~Multiplication() {}
    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

class Division : public BinaryOperation
{
public:
    using BinaryOperation::BinaryOperation;
    ~Division() {}
    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

class Modulus : public BinaryOperation
{
public:
    using BinaryOperation::BinaryOperation;
    ~Modulus() {}
    std::string GetMneumonic(Type type) const override;
    std::string GetOperation() const override;
};

#endif
