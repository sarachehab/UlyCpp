#ifndef AST_IDENTIFIER_HPP
#define AST_IDENTIFIER_HPP

#include "../ast_node.hpp"

class Identifier : public Node
{
private:
    std::string identifier_;

public:
    Identifier(std::string *identifier) : identifier_(*identifier) { delete identifier; };
    ~Identifier(){};

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;

    std::string GetIdentifier() const;
};

#endif
