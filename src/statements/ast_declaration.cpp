#include "../../include/statements/ast_declaration.hpp"

void Declaration::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    TypedefDefinition *typedef_definition = dynamic_cast<TypedefDefinition *>(type_specifier_);
    if (typedef_definition)
    {
        return;
    }

    Specifier *specifier = dynamic_cast<Specifier *>(type_specifier_);
    specifier->DefineSpecifier();

    if (declarator_list_ == nullptr)
    {
        return;
    }

    // Get size of atomic type
    Type type = GetType();
    int type_size = types_size.at(type);

    // Iterate over all declarations
    for (auto declarator : declarator_list_->get_nodes())
    {
        Assignment *assignment = dynamic_cast<Assignment *>(declarator);
        Identifier *identifier = dynamic_cast<Identifier *>(declarator);
        ArrayDeclarator *array_declarator = dynamic_cast<ArrayDeclarator *>(declarator);
        PointerDeclarator *pointer_declarator = dynamic_cast<PointerDeclarator *>(declarator);
        int offset = context.get_stack_offset();

        // Initialization
        if (assignment != nullptr)
        {
            assignment->DeclareLocalScope(type, offset, stream, context);
        }

        // Simple declaration
        else if (identifier != nullptr)
        {
            // Increase stack offset to account for new variable
            context.increase_stack_offset(type_size);

            // Get variable name
            std::string variable_name = identifier->GetIdentifier();

            // Add variable to bindings
            Variable variable_specs(false, false, type, offset, 0);
            context.define_variable(variable_name, variable_specs);
        }

        else if (array_declarator != nullptr)
        {
            // Get array size
            int array_size = array_declarator->GetSize(context);

            if (array_declarator->GetSize(context) == -1)
            {
                throw std::runtime_error("Declaration EmitRISC: Array size not specified");
            }

            // Increase stack offset to account for new variable
            context.increase_stack_offset(type_size * array_size);

            // Get variable name
            std::string variable_name = array_declarator->GetIdentifier();

            // Add variable to bindings
            Variable variable_specs(false, true, array_size, type, offset, 0);
            context.define_variable(variable_name, variable_specs);
        }

        else if (pointer_declarator != nullptr)
        {
            // Increase stack offset to account for new variable
            context.increase_stack_offset(types_size.at(Type::_INT));

            // Get variable name
            std::string variable_name = pointer_declarator->GetIdentifier();

            // Add variable to bindings
            int number_dereferences = pointer_declarator->GetDereferenceNumber();
            Variable variable_specs(true, false, type, offset, number_dereferences);
            context.define_variable(variable_name, variable_specs);
        }

        else
        {
            throw std::runtime_error("Declaration EmitRISC: Unknown declarator type");
        }
    }
}

void Declaration::DeclareGlobal(std::ostream &stream, Context &context, std::string passed_reg) const
{
    TypedefDefinition *typedef_definition = dynamic_cast<TypedefDefinition *>(type_specifier_);
    if (typedef_definition)
    {
        return;
    }

    Specifier *specifier = dynamic_cast<Specifier *>(type_specifier_);
    specifier->DefineSpecifier();

    if (declarator_list_ == nullptr)
    {
        return;
    }

    // Get size of atomic type
    Type type = GetType();
    int type_size = types_size.at(type);

    // Iterate over all declarations
    for (auto declarator_ : declarator_list_->get_nodes())
    {
        Assignment *assignment = dynamic_cast<Assignment *>(declarator_);
        Identifier *identifier = dynamic_cast<Identifier *>(declarator_);
        ArrayDeclarator *array_declarator = dynamic_cast<ArrayDeclarator *>(declarator_);
        PointerDeclarator *pointer_declarator = dynamic_cast<PointerDeclarator *>(declarator_);
        Declarator *declarator = dynamic_cast<Declarator *>(declarator_);

        int offset = context.get_stack_offset();

        // Initialization
        if (assignment != nullptr)
        {
            // Get number of elements if array
            int array_size = assignment->GetSize(context);

            // Determine if array
            bool is_array = assignment->IsArrayInitialization();
            bool is_pointer = assignment->IsPointerInitialization();
            int number_dereferences = assignment->GetDereferenceNumber();

            // Get variable name
            std::string global_name = assignment->GetIdentifier();
            Global global_specs(is_pointer, is_array, array_size, type, number_dereferences);

            // Evaluate expression and store in variable
            assignment->InitializeGlobals(stream, context, global_specs);

            // Add variable to bindings
            context.define_global(global_name, global_specs);
        }

        // Simple declaration
        else if (identifier != nullptr)
        {
            // Get variable name
            std::string global_name = identifier->GetIdentifier();

            // Add variable to bindings
            Global global_specs = Global(false, false, type, 0);
            context.define_global(global_name, global_specs);
        }

        else if (array_declarator != nullptr)
        {
            // Get array size
            int array_size = array_declarator->GetSize(context);

            if (array_declarator->GetSize(context) == -1)
            {
                throw std::runtime_error("Declaration EmitRISC: Array size not specified");
            }

            // Get variable name
            std::string global_name = array_declarator->GetIdentifier();

            // Add variable to bindings
            int number_dereferences = array_declarator->GetDereferenceNumber();
            Global global_specs(false, true, array_size, type, number_dereferences);
            context.define_global(global_name, global_specs);
        }

        else if (pointer_declarator != nullptr)
        {
            // Get variable name
            std::string global_name = pointer_declarator->GetIdentifier();

            // Add variable to bindings
            int number_dereferences = pointer_declarator->GetDereferenceNumber();
            Global global_specs(true, false, type, number_dereferences);
            context.define_global(global_name, global_specs);
        }

        // Function external declaration
        else if (declarator != nullptr)
        {
            // Get function name
            std::string function_name = declarator->GetIdentifier();

            // Define function return value and parameters
            bool return_is_pointer = declarator->IsPointer();
            int number_dereferences = declarator->GetDereferenceNumber();
            ReturnValue return_value = ReturnValue(return_is_pointer, false, type, number_dereferences);
            std::vector<Parameter> arguments = declarator->GetParameters(context);

            // Define function for later access in context
            Function function = Function(return_value, arguments);
            context.define_function(function_name, function);
        }

        else
        {
            throw std::runtime_error("Declaration DeclareGlobal: Unknown declarator type");
        }
    }
}

void Declaration::Print(std::ostream &stream) const
{
    type_specifier_->Print(stream);
    stream << " ";

    if (declarator_list_)
    {
        declarator_list_->Print(stream);
    }

    stream << ";" << std::endl;
}

int Declaration::GetScopeOffset(Context &context) const
{
    // Get size of atomic type
    Specifier *type_specifier = dynamic_cast<Specifier *>(type_specifier_);

    // Get size of atomic type
    Type type = type_specifier->GetType();
    int type_size = types_size.at(type);

    int total_size = 0;

    if (declarator_list_ != nullptr)
    {
        // Take into consideration size of array if it is an array
        for (auto declaration_ : declarator_list_->get_nodes())
        {
            ArrayDeclarator *array_declarator = dynamic_cast<ArrayDeclarator *>(declaration_);
            Assignment *assignment = dynamic_cast<Assignment *>(declaration_);
            PointerDeclarator *pointer_declarator = dynamic_cast<PointerDeclarator *>(declaration_);
            Identifier *identifier = dynamic_cast<Identifier *>(declaration_);

            if (array_declarator != nullptr)
            {
                int actual_type_size = array_declarator->IsPointer() ? types_size.at(Type::_INT) : type_size;
                total_size = total_size + actual_type_size * array_declarator->GetSize(context);
            }
            else if (assignment != nullptr)
            {
                int actual_size = assignment->IsPointerInitialization() ? types_size.at(Type::_INT) : type_size;
                type_size = total_size + type_size * assignment->GetSize(context);
            }
            else if (pointer_declarator != nullptr)
            {
                type_size = total_size + types_size.at(Type::_INT);
            }
            else if (identifier != nullptr)
            {
                type_size = total_size + type_size;
            }

            // Align offset to 4 bytes
            if (type_size % 4 != 0)
            {
                type_size = type_size + 4 - (type_size % 4);
            }
        }
    }
    return total_size;
}

Type Declaration::GetType() const
{

    Specifier *type_specifier = dynamic_cast<Specifier *>(type_specifier_);

    if (type_specifier != nullptr)
    {
        return type_specifier->GetType();
    }

    throw std::runtime_error("Declaration::GetType - Not specifier");
}

Node *Declaration::ApplyIndividualTypedef(Node *declaration)
{
    TypedefSpecifier *typedef_specifier = dynamic_cast<TypedefSpecifier *>(type_specifier_);
    if (typedef_specifier != nullptr)
    {
        Declarator *typedef_placeholder_ = typedef_specifier->GetRootNode();

        if (typedef_placeholder_ != nullptr)
        {

            Assignment *assignment = dynamic_cast<Assignment *>(declaration);

            if (assignment != nullptr)
            {
                assignment->ApplyTypedef(typedef_placeholder_);
            }
            else
            {
                typedef_placeholder_->DefineRoot(declaration);
                declaration = typedef_placeholder_;
            }
        }
    }
    return declaration;
}

void Declaration::ApplyTypedef()
{
    TypedefDefinition *typedef_definition = dynamic_cast<TypedefDefinition *>(type_specifier_);
    if (typedef_definition)
    {
        return;
    }

    if (declarator_list_ != nullptr)
    {
        std::vector<Node *> declarations_list = declarator_list_->get_nodes();

        for (int i = 0; i < declarations_list.size(); i++)
        {
            declarations_list[i] = ApplyIndividualTypedef(declarations_list[i]);
        }
    }
}
