#include "../../include/pointers/ast_dereference.hpp"

std::string Dereference::GetMneumonic(Type type) const
{
    return "Dereference::GetMneumonic - unused";
}

std::string Dereference::GetOperation() const
{
    std::string s = "";
    for (int i = 0; i < PointerDereferenceCount(); i++)
    {
        s += "*";
    }
    return s;
}

std::string Dereference::GetIdentifier() const
{
    ArrayAccess *array_access = dynamic_cast<ArrayAccess *>(expression_);
    Identifier *identifier = dynamic_cast<Identifier *>(expression_);
    Dereference *dereference = dynamic_cast<Dereference *>(expression_);

    if (array_access != nullptr)
    {
        return array_access->GetIdentifier();
    }
    else if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    else if (dereference != nullptr)
    {
        return dereference->GetIdentifier();
    }

    throw std::runtime_error("Dereference::GetIdentifier - unknown expression type");
}

Type Dereference::GetType(Context &context) const
{
    Variable variable_specs = context.get_variable(GetIdentifier());

    if (variable_specs.dereferences_number == PointerDereferenceCount())
    {
        return variable_specs.type;
    }
    return Type::_INT;
}

bool Dereference::IsPointer(Context &context) const
{
    Variable variable_specs = context.get_variable(GetIdentifier());

    if (variable_specs.dereferences_number == PointerDereferenceCount())
    {
        return true;
    }
    return false;
}

int Dereference::PointerDereferenceCount() const
{
    int count = 1;
    Dereference *dereference = dynamic_cast<Dereference *>(expression_);

    if (dereference != nullptr)
    {
        count += dereference->PointerDereferenceCount();
    }

    return count;
}

void Dereference::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    Type type = GetType(context);

    std::string address_register = context.get_register(Type::_INT);
    InitialOffset(stream, context, address_register);

    ExecutePathDereference(stream, context, address_register);
    stream << context.load_instruction(type) << " " << passed_reg << ", 0(" << address_register << ")" << std::endl;

    context.deallocate_register(address_register);
}

void Dereference::ExecutePathDereference(std::ostream &stream, Context &context, std::string address_register) const
{
    std::string variable_identifier = GetIdentifier();

    Dereference *dereference = dynamic_cast<Dereference *>(expression_);

    if (dereference != nullptr)
    {
        dereference->ExecutePathDereference(stream, context, address_register);
    }

    stream << context.load_instruction(Type::_INT) << " " << address_register << ", 0(" << address_register << ")" << std::endl;
}

void Dereference::InitialOffset(std::ostream &stream, Context &context, std::string address_reg) const
{
    std::string variable_identifier = GetIdentifier();
    Variable variable_specs = context.get_variable(variable_identifier);
    Scope scope = variable_specs.scope;
    Type type = GetType(context);

    if (scope == Scope::_LOCAL)
    {
        stream << "addi " << address_reg << ", s0, " << variable_specs.offset << std::endl;
    }
    else if (scope == Scope::_GLOBAL)
    {
        std::string global_label = "global_" + variable_identifier;
        stream << "lui " << address_reg << ", %hi(" << global_label << ")" << std::endl;
        stream << "addi " << address_reg << ", " << address_reg << ", %lo(" << global_label << ")" << std::endl;
    }

    ArrayAccess *array_access = dynamic_cast<ArrayAccess *>(expression_);
    if (array_access != nullptr)
    {
        std::string index_reg = context.get_register(Type::_INT);
        array_access->GetIndex(stream, context, address_reg, type);
        stream << "add " << address_reg << ", " << address_reg << ", " << index_reg << std::endl;
        context.deallocate_register(index_reg);
    }
}

bool Dereference::IsPointerOperation(Context &context) const
{
    return IsPointer(context);
}
