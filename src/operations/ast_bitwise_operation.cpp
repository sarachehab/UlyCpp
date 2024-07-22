#include "../../include/operations/ast_bitwise_operation.hpp"

std::string InclusiveOr::GetMneumonic(Type type) const { return "or "; }
std::string InclusiveOr::GetOperation() const { return " | "; }

std::string ExclusiveOr::GetMneumonic(Type type) const { return "xor "; }
std::string ExclusiveOr::GetOperation() const { return " ^ "; }

std::string BitwiseAnd::GetMneumonic(Type type) const { return "and "; }
std::string BitwiseAnd::GetOperation() const { return " & "; }

std::string LeftShift::GetMneumonic(Type type) const { return "sll "; }
std::string LeftShift::GetOperation() const { return " << "; }

std::string RightShift::GetMneumonic(Type type) const { return "sra "; }
std::string RightShift::GetOperation() const { return " >> "; }

std::string OneComplement::GetMneumonic(Type type) const { return "not "; }
std::string OneComplement::GetOperation() const { return " ~ "; }
