#include "../../include/statements/ast_declaration.hpp"

void Declaration::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Get size of atomic type
    Type type = GetType();
    int type_size = types_size.at(type);

    // Iterate over all declarations
    NodeList *declarator_list = dynamic_cast<NodeList *>(declarator_list_);
    for (auto declarator : declarator_list->get_nodes())
    {
        Assignment *assignment = dynamic_cast<Assignment *>(declarator);
        Identifier *identifier = dynamic_cast<Identifier *>(declarator);
        DirectDeclarator *direct_declarator = dynamic_cast<DirectDeclarator *>(declarator);
        ArrayDeclarator *array_declarator = dynamic_cast<ArrayDeclarator *>(declarator);

        int offset = context.get_stack_offset();

        // Initialization
        if (assignment != nullptr)
        {
            // Get number of elements if array
            int size = assignment->GetSize();

            // Determine if array
            bool is_array = assignment->IsArrayInitialization();

            // Increase stack offset to account for new variable
            context.increase_stack_offset(type_size * size);

            // Get variable name
            std::string variable_name = assignment->GetIdentifier();

            // Add variable to bindings
            Variable variable_specs(false, is_array, type, Scope::_LOCAL, offset);
            context.define_variable(variable_name, variable_specs);

            // Evaluate expression and store in variable
            assignment->EmitRISC(stream, context, passed_reg);
        }

        // Simple declaration
        else if (identifier != nullptr)
        {
            // Increase stack offset to account for new variable
            context.increase_stack_offset(type_size);

            // Get variable name
            std::string variable_name = identifier->GetIdentifier();

            // Add variable to bindings
            Variable variable_specs(false, false, type, Scope::_LOCAL, offset);
            context.define_variable(variable_name, variable_specs);
        }

        else if (array_declarator != nullptr)
        {
            // Get array size
            int array_size = array_declarator->GetSize();

            if (array_declarator->GetSize() == -1)
            {
                throw std::runtime_error("Declaration EmitRISC: Array size not specified");
            }

            // Increase stack offset to account for new variable
            context.increase_stack_offset(type_size * array_size);

            // Get variable name
            std::string variable_name = array_declarator->GetIdentifier();

            // Add variable to bindings
            Variable variable_specs(false, true, type, Scope::_LOCAL, offset);
            context.define_variable(variable_name, variable_specs);
        }

        // Function external declaration
        else if (direct_declarator != nullptr)
        {
            // Get function name
            std::string function_name = direct_declarator->GetIdentifier();

            // Define function return value and parameters
            ReturnValue return_value = ReturnValue(false, false, type);
            std::vector<Parameter> arguments = direct_declarator->GetParameters(context);

            // Define function for later access in context
            Function function = Function(return_value, arguments);
            context.define_function(function_name, function);
        }

        else
        {
            throw std::runtime_error("Declaration EmitRISC: Unknown declarator type");
        }
    }
}

void Declaration::Print(std::ostream &stream) const
{
    type_specifier_->Print(stream);
    stream << " ";

    declarator_list_->Print(stream);
    stream << ";" << std::endl;
}

int Declaration::GetScopeOffset(Context &context) const
{
    // Get size of atomic type
    TypeSpecifier *type_specifier = dynamic_cast<TypeSpecifier *>(type_specifier_);
    Type type = type_specifier->GetType();
    int type_size = types_size.at(type);

    NodeList *declarator_list = dynamic_cast<NodeList *>(declarator_list_);

    // Take into consideration size of array if it is an array
    Assignment *assignment = dynamic_cast<Assignment *>(declarator_list->get_nodes()[0]);
    ArrayDeclarator *array_declarator = dynamic_cast<ArrayDeclarator *>(declarator_list->get_nodes()[0]);

    if (assignment != nullptr)
    {
        type_size *= assignment->GetSize();
    }
    else if (array_declarator != nullptr)
    {
        type_size *= array_declarator->GetSize();
    }

    // Return total size of all declarations
    return type_size * declarator_list->get_nodes().size();
}

Type Declaration::GetType() const
{
    TypeSpecifier *type_specifier = dynamic_cast<TypeSpecifier *>(type_specifier_);
    return type_specifier->GetType();
}
