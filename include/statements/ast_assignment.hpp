#ifndef AST_ASSIGNMENT_HPP
#define AST_ASSIGNMENT_HPP

#include "../ast_node.hpp"
#include "../primitives/ast_identifier.hpp"
#include "../primitives/ast_constant.hpp"
#include "../arrays/ast_array_declarator.hpp"
#include "../arrays/ast_array_initializer.hpp"
#include "../arrays/ast_array_access.hpp"
#include "../pointers/ast_pointer_declarator.hpp"
#include "../ast_direct_declarator.hpp"
#include "../pointers/ast_address_of.hpp"
#include "../pointers/ast_dereference.hpp"
#include "../chars/ast_string_literal.hpp"

class AssignmentList : public NodeList
{
public:
    using NodeList::NodeList;
    ~AssignmentList() {}
};

class Assignment : public Node
{
private:
    Node *unary_expression_;
    Node *expression_;

public:
    Assignment(Node *unary_expression, Node *expression) : unary_expression_(unary_expression), expression_(expression) {}
    ~Assignment()
    {
        delete unary_expression_;
        delete expression_;
    }

    /**
     * @brief Get the identifier name
     * @return Identifier name
     */
    std::string GetIdentifier() const;

    /**
     * @brief Get the size of the array
     */
    int GetSize() const;

    /**
     * @brief Check if the assignment is an array initialization
     *
     * @return true if the assignment is an array initialization
     */
    bool IsArrayInitialization() const;

    /**
     * @brief Check if the assignment is a pointer initialization
     *
     * @return true if the assignment is a pointer initialization
     */
    bool IsPointerInitialization() const;

    /**
     * @brief Perform initialization of the global variable
     */
    void InitializeGlobals(std::ostream &stream, Context &context, Global &global_specs) const;
    void DeclareLocalScope(Type type, int offset, std::ostream &stream, Context &context) const;
    int GetDereferenceNumber() const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
