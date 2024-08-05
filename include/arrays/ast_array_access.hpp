#ifndef AST_ARRAY_ACCESS_HPP
#define AST_ARRAY_ACCESS_HPP

#include "../ast_node.hpp"
#include "../primitives/ast_identifier.hpp"
#include "../operations/ast_operand.hpp"

class ArrayAccess : public Operand
{
private:
    Node *identifier_;
    Node *index_;

public:
    ArrayAccess(Node *identifier, Node *index) : identifier_(identifier), index_(index) {}
    ~ArrayAccess()
    {
        delete identifier_;
        delete index_;
    }

    std::string GetIdentifier() const;
    Type GetType(Context &context) const override;

    /**
     * @brief Get the index of the array access
     *
     * @param stream output stream to write to
     * @param context current context
     * @param passed_reg register to store the index
     */
    void GetIndex(std::ostream &stream, Context &context, std::string passed_reg, Type type) const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const;
    void Print(std::ostream &stream) const;
};

#endif
