#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>

#include "context/context.hpp"

class Node
{
protected:
    std::vector<Node *> branches_;

public:
    Node() {};
    virtual ~Node();

    /**
     * @brief Emit RISC-V assembly code
     *
     * @param stream Output stream
     * @param context Context object
     * @param passed_reg Register to pass to the next node
     */
    virtual void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const = 0;

    /**
     * @brief Print the node
     *
     * @param stream Output stream
     */
    virtual void Print(std::ostream &stream) const = 0;
};

// Represents a list of nodes.
class NodeList : public Node
{
protected:
    std::vector<Node *> nodes_;

public:
    NodeList(Node *first_node) : nodes_({first_node}) {}

    ~NodeList()
    {
        for (auto node : nodes_)
        {
            delete node;
        }
    }

    /**
     * @brief Add a node to the list
     *
     * @param item Node to add
     */
    void PushBack(Node *item);

    /**
     * @brief Get nodes from NodeList
     *
     * @return List of nodes
     */
    std::vector<Node *> get_nodes() const;

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    virtual void Print(std::ostream &stream) const override;
};

#endif
