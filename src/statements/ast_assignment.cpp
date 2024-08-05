#include "../../include/statements/ast_assignment.hpp"

void Assignment::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Get variable specifications
    Variable variable_specs = context.get_variable(GetIdentifier());
    Type type = variable_specs.type;

    // Get offset of variable within current stack frame
    int offset = variable_specs.offset;

    // Define operation type for expression
    context.set_operation_type(type);

    // Emit expression to specified register
    std::string reg = context.get_register(type);
    expression_->EmitRISC(stream, context, reg);

    // If the expression is an array initializer, save the array
    if (IsArrayInitialization())
    {
        dynamic_cast<ArrayInitializer *>(expression_)->Save(stream, context, offset, type);
    }

    else
    {
        Identifier *identifier = dynamic_cast<Identifier *>(unary_expression_);
        ArrayAccess *array_access = dynamic_cast<ArrayAccess *>(unary_expression_);

        // If atomic identifier, load expression into variable
        if (identifier != nullptr)
        {
            // Load expression into variable
            stream << context.store_instruction(type) << " " << reg << ", " << offset << "(sp)" << std::endl;
        }

        // If array access, load expression into specific element by first evaluating index
        else if (array_access != nullptr)
        {
            // Get index of specific element
            std::string index_register = context.get_register(Type::_INT);
            array_access->GetIndex(stream, context, index_register, type);

            // Get variable offset
            stream << context.store_instruction(type) << " " << reg << ", " << variable_specs.offset << "(" << index_register << ")" << std::endl;

            // Deallocate register
            context.deallocate_register(index_register);
        }

        else
        {
            throw std::runtime_error("Assignment EmitRISC: Not an identifier or array access");
        }
    }

    // Deallocate register
    context.deallocate_register(reg);

    // Pop operation type
    context.pop_operation_type();
}

void Assignment::Print(std::ostream &stream) const
{
    unary_expression_->Print(stream);
    stream << " = ";
    expression_->Print(stream);
    stream << ";" << std::endl;
}

std::string Assignment::GetIdentifier() const
{
    Identifier *identifier = dynamic_cast<Identifier *>(unary_expression_);
    ArrayAccess *array_access = dynamic_cast<ArrayAccess *>(unary_expression_);
    ArrayDeclarator *array_declarator = dynamic_cast<ArrayDeclarator *>(unary_expression_);

    if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    else if (array_access != nullptr)
    {
        return array_access->GetIdentifier();
    }
    else if (array_declarator != nullptr)
    {
        return array_declarator->GetIdentifier();
    }

    throw std::runtime_error("Assignment GetIdentifier: Not an identifier");
}

int Assignment::GetSize() const
{
    ArrayDeclarator *array_declarator = dynamic_cast<ArrayDeclarator *>(unary_expression_);

    // Get size specified in array declarator
    if (array_declarator != nullptr)
    {
        // If no size specified in array declarator, get size from array initializer
        if (array_declarator->GetSize() == -1)
        {
            return dynamic_cast<ArrayInitializer *>(expression_)->GetSize();
        }
        return array_declarator->GetSize();
    }

    return 1;
}

bool Assignment::IsArrayInitialization() const
{
    return dynamic_cast<ArrayDeclarator *>(unary_expression_) != nullptr;
}
