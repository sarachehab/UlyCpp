#include "../../include/statements/ast_assignment.hpp"

void Assignment::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Get variable specifications
    Variable variable_specs = context.get_variable(GetIdentifier());
    Type type = variable_specs.is_pointer ? Type::_INT : variable_specs.type;

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
        dynamic_cast<ArrayInitializer *>(expression_)->Save(stream, context, variable_specs, GetIdentifier());
    }

    else
    {
        Identifier *identifier = dynamic_cast<Identifier *>(unary_expression_);
        ArrayAccess *array_access = dynamic_cast<ArrayAccess *>(unary_expression_);
        PointerDeclarator *pointer_declarator = dynamic_cast<PointerDeclarator *>(unary_expression_);
        AddressOf *address_of = dynamic_cast<AddressOf *>(unary_expression_);
        Dereference *dereference = dynamic_cast<Dereference *>(unary_expression_);

        // If atomic identifier, load expression into variable
        if (identifier != nullptr)
        {
            if (variable_specs.scope == Scope::_LOCAL)
            {
                stream << context.store_instruction(type) << " " << reg << ", " << offset << "(s0)" << std::endl;
            }

            else if (variable_specs.scope == Scope::_GLOBAL)
            {
                std::string global_memory_location = "global_" + GetIdentifier();
                std::string global_memory_register = context.get_register(Type::_INT);

                // Access global memory by targetting global label
                stream << "lui " << global_memory_register << ", " << "%hi(" << global_memory_location << ")" << std::endl;
                stream << context.store_instruction(type) << " " << reg << ", %lo(" << global_memory_location << ")(" << global_memory_register << ")" << std::endl;
                context.deallocate_register(global_memory_register);
            }

            else
            {
                throw std::runtime_error("Assignment EmitRISC: Invalid scope in Identifier");
            }
        }

        // If array access, load expression into specific element by first evaluating index
        else if (array_access != nullptr)
        {
            type = array_access->IsPointerOperation(context) ? Type::_INT : array_access->GetType(context);

            // Get index of specific element
            std::string index_register = context.get_register(Type::_INT);
            array_access->GetIndex(stream, context, index_register, type);

            // If local scope, access variable through offset specified in bindings
            if (variable_specs.scope == Scope::_LOCAL)
            {
                if (variable_specs.is_array)
                {
                    // Add index to base pointer
                    stream << "add " << index_register << ", " << index_register << ", s0" << std::endl;
                    stream << "addi " << index_register << ", " << index_register << ", " << offset << std::endl;
                }
                else if (variable_specs.is_pointer)
                {
                    // Pointers points to first item in list
                    std::string pointer_register = context.get_register(Type::_INT);
                    stream << context.load_instruction(Type::_INT) << " " << pointer_register << ", " << offset << "(s0)" << std::endl;
                    stream << "add " << index_register << ", " << index_register << ", " << pointer_register << std::endl;
                    context.deallocate_register(pointer_register);
                }
                else
                {
                    throw std::runtime_error("Assignment EmitRISC: Variable is not a pointer or array in ArrayAccess LOCAL");
                }

                // Get variable offset
                stream << context.store_instruction(type) << " " << reg << ", 0(" << index_register << ")" << std::endl;
            }

            // If global scope, access global memory by targetting global label
            else if (variable_specs.scope == Scope::_GLOBAL)
            {
                std::string global_memory_location = "global_" + GetIdentifier();
                std::string global_memory_register = context.get_register(Type::_INT);

                // Access global memory by targetting global label
                stream << "lui " << global_memory_register << ", " << "%hi(" << global_memory_location << ")" << std::endl;
                stream << "add " << global_memory_register << ", " << global_memory_register << ", " << index_register << std::endl;
                stream << context.store_instruction(type) << " " << reg << ", %lo(" << global_memory_location << ")(" << global_memory_register << ")" << std::endl;

                context.deallocate_register(global_memory_register);
            }

            else
            {
                throw std::runtime_error("Assignment EmitRISC: Invalid scope in ArrayAccess");
            }

            // Deallocate register
            context.deallocate_register(index_register);
        }

        else if (pointer_declarator != nullptr)
        {
            // If local scope, access variable through offset specified in bindings
            if (variable_specs.scope == Scope::_LOCAL)
            {
                stream << context.store_instruction(type) << " " << reg << ", " << variable_specs.offset << "(s0)" << std::endl;
            }

            // If global scope, access global memory by targetting global label
            else if (variable_specs.scope == Scope::_GLOBAL)
            {
                std::string global_memory_location = "global_" + GetIdentifier();
                std::string global_memory_register = context.get_register(Type::_INT);

                // Access global memory by targetting global label
                stream << "lui " << global_memory_register << ", " << "%hi(" << global_memory_location << ")" << std::endl;
                stream << context.store_instruction(type) << " " << reg << ", %lo(" << global_memory_location << ")(" << global_memory_register << ")" << std::endl;
                context.deallocate_register(global_memory_register);
            }

            else
            {
                throw std::runtime_error("Assignment EmitRISC: Invalid scope in PointerDeclarator");
            }
        }

        else if (address_of != nullptr)
        {
            // If local scope, access variable through offset specified in bindings
            if (variable_specs.scope == Scope::_LOCAL)
            {
                stream << context.store_instruction(type) << " " << reg << ", " << variable_specs.offset << "(s0)" << std::endl;
            }

            // If global scope, access global memory by targetting global label
            else if (variable_specs.scope == Scope::_GLOBAL)
            {
                std::string global_memory_location = "global_" + GetIdentifier();
                std::string global_memory_register = context.get_register(Type::_INT);

                // Access global memory by targetting global label
                stream << "lui " << global_memory_register << ", " << "%hi(" << global_memory_location << ")" << std::endl;
                stream << context.store_instruction(type) << " " << reg << ", %lo(" << global_memory_location << ")(" << global_memory_register << ")" << std::endl;
                context.deallocate_register(global_memory_register);
            }

            else
            {
                throw std::runtime_error("Assignment EmitRISC: Invalid scope in AddressOf");
            }
        }

        else if (dereference != nullptr)
        {
            std::string address_register = context.get_register(Type::_INT);
            Type type = dereference->GetType(context);

            dereference->InitialOffset(stream, context, address_register);
            dereference->ExecutePathDereference(stream, context, address_register);
            stream << context.store_instruction(type) << " " << reg << ", 0(" << address_register << ")" << std::endl;

            context.deallocate_register(address_register);
        }

        else
        {
            throw std::runtime_error("Assignment EmitRISC: Not an identifier, array access or pointer declarator");
        }
    }

    // Deallocate register
    context.deallocate_register(reg);

    // Pop operation type
    context.pop_operation_type();
}

void Assignment::InitializeGlobals(std::ostream &stream, Context &context, Global &global_specs) const
{

    Constant *constant = dynamic_cast<Constant *>(expression_);
    StringLiteral *string_literal = dynamic_cast<StringLiteral *>(expression_);
    ArrayInitializer *array_initializer = dynamic_cast<ArrayInitializer *>(expression_);

    if (constant != nullptr)
    {
        constant->SaveValue(global_specs);
    }

    else if (string_literal != nullptr)
    {
        string_literal->SaveValue(context, global_specs);
    }

    else if (array_initializer != nullptr)
    {
        array_initializer->InitializeGlobals(stream, context, global_specs);
    }

    else
    {
        throw std::runtime_error("Assignment InitializeGlobals: Not a constant or string literal");
    }
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
    Dereference *dereference = dynamic_cast<Dereference *>(unary_expression_);
    AddressOf *address_of = dynamic_cast<AddressOf *>(unary_expression_);
    Declarator *declarator = dynamic_cast<Declarator *>(unary_expression_);

    if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    else if (array_access != nullptr)
    {
        return array_access->GetIdentifier();
    }
    else if (declarator != nullptr)
    {
        return declarator->GetIdentifier();
    }
    else if (dereference != nullptr)
    {
        return dereference->GetIdentifier();
    }
    else if (address_of != nullptr)
    {
        return address_of->GetIdentifier();
    }

    throw std::runtime_error("Assignment GetIdentifier: Not an identifier, array access, array declarator, declarator");
}

int Assignment::GetSize(Context &context) const
{
    ArrayDeclarator *array_declarator = dynamic_cast<ArrayDeclarator *>(unary_expression_);

    // Get size specified in array declarator
    if (array_declarator != nullptr)
    {
        // If no size specified in array declarator, get size from array initializer
        if (array_declarator->GetSize(context) == -1)
        {
            return dynamic_cast<ArrayInitializer *>(expression_)->GetSize();
        }
        return array_declarator->GetSize(context);
    }

    return 1;
}

bool Assignment::IsArrayInitialization() const
{
    return dynamic_cast<ArrayDeclarator *>(unary_expression_) != nullptr;
}

bool Assignment::IsPointerInitialization() const
{
    Declarator *declarator = dynamic_cast<Declarator *>(unary_expression_);
    if (declarator)
    {
        return declarator->IsPointer();
    }

    return false;
}

void Assignment::DeclareLocalScope(Type type, int offset, std::ostream &stream, Context &context) const
{
    // Get number of elements if array
    int array_size = GetSize(context);

    // Determine if array
    bool is_array = IsArrayInitialization();
    bool is_pointer = IsPointerInitialization();

    // Increase stack offset to account for new variable
    Type actual_type = is_pointer ? Type::_INT : type;
    int actual_type_size = types_size.at(actual_type);
    context.increase_stack_offset(actual_type_size * array_size);

    // Get variable name
    std::string variable_name = GetIdentifier();

    // Add variable to bindings
    int number_dereferences = GetDereferenceNumber();
    Variable variable_specs(is_pointer, is_array, array_size, type, offset, number_dereferences);
    context.define_variable(variable_name, variable_specs);

    // Evaluate expression and store in variable
    EmitRISC(stream, context, "unused");
}

int Assignment::GetDereferenceNumber() const
{
    Declarator *declarator = dynamic_cast<Declarator *>(unary_expression_);
    if (declarator != nullptr)
    {
        return declarator->GetDereferenceNumber();
    }

    return 0;
}
