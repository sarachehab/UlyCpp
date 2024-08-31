#ifndef AST_TYPEDEF_SPECIFIER_HPP
#define AST_TYPEDEF_SPECIFIER_HPP

#include "../ast_node.hpp"
#include "../specifiers/ast_specifier.hpp"
#include "../specifiers/ast_type_specifier.hpp"
#include "../pointers/ast_pointer_declarator.hpp"

class TypedefSpecifier : public Specifier
{
private:
    std::string type_name_;
    Specifier *typedef_specifier_;
    TypedefSpec typedef_spec;

public:
    TypedefSpecifier(std::string *type_name) : type_name_(*type_name)
    {
        DefineSpecifier();
        delete type_name;
    }
    ~TypedefSpecifier()
    {
        if (typedef_specifier_ != nullptr)
        {
            delete typedef_specifier_;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;

    std::string GetIdentifier() const;

    void DefineSpecifier();
    Specifier *GetSpecifier() const;
    Declarator *GetRootNode() const;

    Type GetType() const override;
    void DefineSpecifier() const override;
};

#endif
