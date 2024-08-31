#ifndef CONTEXT_TYPEDEF_HPP
#define CONTEXT_TYPEDEF_HPP

#include <string>
#include <unordered_map>
#include "context_types.hpp"

struct TypedefSpec
{
    int number_pointers_;
    std::string base_class_ = "";
    Type type_ = Type::_VOID;

    TypedefSpec()
        : number_pointers_(0), base_class_("empty"), type_(Type::_VOID) {}

    TypedefSpec(Type type, int number_pointers)
        : number_pointers_(number_pointers), base_class_(""), type_(type) {}

    TypedefSpec(std::string base_class, int number_pointers)
        : number_pointers_(number_pointers), base_class_(base_class), type_(Type::_STRUCT) {}
};

typedef std::unordered_map<std::string, TypedefSpec> TypedefCorrespondance;

#endif
