#ifndef AST_ENUMERATOR_SPECIFIER_HPP
#define AST_ENUMERTAOR_SPECIFIER_HPP

#include "../ast_node.hpp"
#include "../specifiers/ast_specifier.hpp"
#include "../primitives/ast_identifier.hpp"
#include "ast_enumerator.hpp"

class EnumeratorSpecifier : public Specifier
{
private:
    std::string *identifier_;
    NodeList *enumerator_list_;

public:
    EnumeratorSpecifier(std::string *identifier) : identifier_(identifier), enumerator_list_(nullptr) { DefineSpecifier(); }
    EnumeratorSpecifier(NodeList *enumerator_list) : identifier_(nullptr), enumerator_list_(enumerator_list) { DefineSpecifier(); }
    EnumeratorSpecifier(std::string *identifier, NodeList *enumerator_list) : identifier_(identifier), enumerator_list_(enumerator_list) { DefineSpecifier(); }

    ~EnumeratorSpecifier()
    {
        if (identifier_)
        {
            delete identifier_;
        }
        if (enumerator_list_)
        {
            delete enumerator_list_;
        }
    }

    void DefineSpecifier() const override;

    virtual Type GetType() const override;
    virtual void Print(std::ostream &stream) const override;

    bool IsSimpleDeclaration() const;
};

#endif
