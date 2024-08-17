#include "../../include/pointers/ast_address_of.hpp"

std::string AddressOf::GetOperation() const
{
    return "&";
}

std::string AddressOf::GetIdentifier() const
{
    Identifier *identifier = dynamic_cast<Identifier *>(expression_);
    AddressOf *address_of = dynamic_cast<AddressOf *>(expression_);
    ArrayAccess *array_access = dynamic_cast<ArrayAccess *>(expression_);

    if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    else if (address_of != nullptr)
    {
        return address_of->GetIdentifier();
    }
    else if (array_access != nullptr)
    {
        return array_access->GetIdentifier();
    }

    throw std::runtime_error("Invalid address of expression");
}

Type AddressOf::GetType(Context &context) const
{
    return Type::_INT;
}

void AddressOf::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    std::string identifier = GetIdentifier();

    // Get the variable specs and output variable type
    Variable variable_specs = context.get_variable(identifier);
    Type type = GetType(context);

    // Check if the expression array_access
    ArrayAccess *array_access = dynamic_cast<ArrayAccess *>(expression_);

    // If the expression is an array access, get the index and calculate the address
    if (array_access)
    {
        std::string index_register = context.get_register(Type::_INT);
        array_access->GetIndex(stream, context, index_register, type);

        if (variable_specs.scope == Scope::_LOCAL)
        {
            if (variable_specs.is_pointer)
            {
                std::string pointer_register = context.get_register(Type::_INT);
                stream << context.load_instruction(Type::_INT) << " " << pointer_register << ", " << variable_specs.offset << "(sp)" << std::endl;
                stream << "add " << passed_reg << ", " << index_register << ", " << pointer_register << std::endl;
                context.deallocate_register(pointer_register);
            }
            else if (variable_specs.is_array)
            {
                stream << "add " << passed_reg << ", " << index_register << ", sp" << std::endl;
                stream << "addi " << passed_reg << ", " << passed_reg << ", " << variable_specs.offset << std::endl;
            }
            else
            {
                throw std::runtime_error("ArrayAccess EmitRISC: Variable is not a pointer or array");
            }
        }

        else if (variable_specs.scope == Scope::_GLOBAL)
        {
            stream << "la " << passed_reg << ", global_" << identifier << std::endl;
            stream << "add " << passed_reg << ", " << passed_reg << ", " << index_register << std::endl;
        }

        else
        {
            throw std::runtime_error("AddressOf EmitRISC: variable_specs.scope is not local or global");
        }

        context.deallocate_register(index_register);
    }

    else
    {
        if (variable_specs.scope == Scope::_LOCAL)
        {
            stream << "addi " << passed_reg << ", sp, " << variable_specs.offset << std::endl;
        }
        else if (variable_specs.scope == Scope::_GLOBAL)
        {
            stream << "la " << passed_reg << ", global_" << identifier << std::endl;
        }
        else
        {
            std::runtime_error("AddressOf EmitRISC: variable_specs.scope is not local or global");
        }
    }
}

std::string AddressOf::GetMneumonic(Type type) const
{
    return "AddressOf::GetMneumonic - unsupported";
}
