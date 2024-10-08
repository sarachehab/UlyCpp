#ifndef AST_PARAMETER_DEFINITION_HPP
#define AST_PARAMETER_DEFINITION_HPP

#include "../ast_node.hpp"
#include "../specifiers/ast_specifier.hpp"
#include "../primitives/ast_identifier.hpp"
#include "../pointers/ast_pointer_declarator.hpp"

class ParameterList : public NodeList
{
private:
    std::vector<Parameter> parameters;

public:
    using NodeList::NodeList;
    ~ParameterList() {}

    std::vector<Parameter> GetParameters(Context &context);
    int GetScopeOffset() const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
};

class ParameterDeclaration : public Node
{
private:
    Node *type_specifier_;
    Node *declarator_;

public:
    ParameterDeclaration(Node *type_specifier, Node *declarator) : type_specifier_(type_specifier), declarator_(declarator) {}
    ~ParameterDeclaration()
    {
        delete type_specifier_;
        delete declarator_;
    }

    Type GetType() const;
    Parameter GetParameter(Context &context, int offset) const;
    std::string GetIdentifier() const;
    int GetSize() const;
    bool IsPointer() const;
    int GetDereferenceNumber() const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
