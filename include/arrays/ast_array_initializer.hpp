#ifndef AST_ARRAY_INITIALIZER_HPP
#define AST_ARRAY_INITIALIZER_HPP

#include "../ast_node.hpp"
#include "../operations/ast_operand.hpp"

class ArrayInitializer : public Node
{
private:
    Node *initializer_list_;

public:
    ArrayInitializer(Node *initializer_list) : initializer_list_(initializer_list) {}
    ~ArrayInitializer()
    {
        delete initializer_list_;
    }

    /**
     * @brief Get the size of the array
     */
    int GetSize() const;

    /**
     * @brief Save the initializer list to the stack
     */
    void Save(std::ostream &stream, Context &context, int initial_offset, Type type) const;

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

#endif
