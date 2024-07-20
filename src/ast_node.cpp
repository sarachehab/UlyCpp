#include "ast_node.hpp"

Node::~Node()
{
    for (auto branch : branches_)
    {
        delete branch;
    }
}

void NodeList::PushBack(Node *item)
{
    nodes_.push_back(item);
}

void NodeList::EmitRISC(std::ostream &stream, Context &context, std::string passedReg) const
{
    for (auto node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->EmitRISC(stream, context, passedReg);
    }
}

void NodeList::Print(std::ostream &stream) const
{
    for (auto node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->Print(stream);
    }
}

std::vector<Node *> NodeList::get_nodes() const
{
    return nodes_;
}
