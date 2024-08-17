#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <unordered_map>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <set>

#include "context_types.hpp"
#include "context_registers.hpp"
#include "context_functions.hpp"
#include "context_variables.hpp"
#include "context_constant.hpp"
#include "context_conversion.hpp"

/**
 * @brief This class represents the context of the program.
 *
 * It contains information on the registers, variables, functions, control flow, operations and constants.
 * It is used to manage the state of the program and generate the assembly code.
 * It is passed on between the different classes through functions like Node::EmitRISC.
 */
class Context
{

public:
    Context();
    ~Context();

    // ============= REGISTER ALLOCATION ==============

    /**
     * @brief This function returns the name of an available register of the given type.
     *
     * This function iterates through the register file to find an available register of the given type.
     * If no register is available, an error is thrown. This could eventually be extended to spill registers.
     *
     * @param type The type of the variable.
     * @return The name of the register.
     */
    std::string get_register(Type type);

    /**
     * @brief This function returns the register to store the return value of a function.
     *
     * @return The return register.
     */
    std::string get_return_register() const;

    /**
     * @brief This function deallocates a register.
     *
     * This function sets the register as available.
     * This function could be extended to handle spillage.
     *
     * @param reg_name The name of the register to deallocate.
     */
    void deallocate_register(std::string reg_name);

    /**
     * @brief This function returns the name of a register given its number.
     *
     * @param reg_number The number of the register.
     * @return The name of the register.
     */
    std::string get_register_name(int reg_number) const;

    /**
     * @brief This function sets the type of a register.
     *
     * This function is used to set the type of a register when a variable is assigned to it.
     *
     * @param reg_name The name of the register.
     * @param type The type of the variable.
     */
    void set_register_type(std::string reg_name, Type type);

    /**
     * @brief This function adds the specified register to the list of currently used registers.
     *
     * This function is used to handle register spillage in cases of function calls
     *
     * @param reg_name The name of the register to add
     */
    void add_register_to_set(std::string reg_name);

    /**
     * @brief This function removes the specified register from the list of currently used registers.
     *
     * This function is used to handle register spillage in cases of function calls
     *
     * @param reg_name The name of the register to remove
     */
    void remove_register_from_set(std::string reg_name);

    /**
     * @brief This function saves the currently used registers to the stack.
     *
     * This function is used to handle register spillage in cases of function calls.
     * The registers are saved to the stack and the register file is reset to an empty state.
     *
     * @param stream The output stream to write the assembly code to.
     */
    void push_registers(std::ostream &stream);

    /**
     * @brief This function restores the previously saved registers from the stack.
     *
     * This function is used to handle register spillage in cases of function calls.
     * The registers are restored from the stack and the register file is reset to the state before the function call.
     *
     * @param stream The output stream to write the assembly code to.
     */
    void pop_registers(std::ostream &stream);

    // ============= STACK MANAGEMENT ==============

    /**
     * @brief This function creates a new scope in the context.
     *
     * This function is used to manage variable scopes and interferences between these scopes.
     */

    // Define new VariableBindings, variables should only be accessible from child scopes.
    // Parent scope should not be able to access variables defined in child scopes.
    void create_new_scope();

    /**
     * @brief This function pops the last scope from the context.
     *
     * This function is used to manage variable scopes and interferences between these scopes.
     */
    void pop_scope();

    /**
     * @brief This function returns the current stack offset.
     *
     * @return The current stack offset.
     */

    int get_stack_offset() const;

    /**
     * @brief This function increases the current stack offset.
     *
     * This function is used to allocate space for variables in the stack.
     *
     * @param offset The offset to increase the stack offset by.
     */

    void increase_stack_offset(int offset);

    /**
     * @brief This function sets the current stack offset.
     */
    void set_stack_offset(int offset);

    // ============= VARIABLE MANAGEMENT ==============

    /**
     * @brief Define a variable in the current scope
     *
     * This function defines a variable in the current scope.
     * If the variable already exists in the current scope, it will be overwritten.
     * The variable can exist in a parent scope.
     * Information on the variable is passed, such as is_pointer, type, offset in memory.
     *
     * @param identifier The name of the variable
     */
    void define_variable(std::string identifier, Variable variable);

    /**
     * @brief Get a variable from the current scope
     *
     * This function returns the specifications of a variable with the given identifier.
     *
     * @param identifier The name of the variable
     */
    Variable get_variable(std::string identifier) const;

    // ============= FUNCTION MANAGEMENT ==============

    /**
     * @brief This function defines a function in the context.
     *
     * It specifies the return value and parameters needed to call a function.
     *
     * @param identifier The identifier of the function.
     * @param function The function to define.
     */
    void define_function(std::string identifier, Function function);

    /**
     * @brief This function returns the specifications of the function with the given identifier.
     *
     * It is used whenever a function is called to determine the types of the return and arguments.
     *
     * @param identifier The identifier of the function.
     * @return The function with the given identifier.
     */
    Function get_function(std::string identifier) const;

    /**
     * @brief This function returns the end statement of the last function defined.
     *
     * @return The end statement of the last function defined.
     */
    std::string get_last_function_end_statement() const;

    /**
     * @brief This function exits the current function scope.
     *
     * It pops the latest stack offset.
     */
    void exit_function();

    /**
     * @brief This function sets the register to store the return value of a function.
     *
     * @param type The type of the return value.
     */
    void set_return_register(Type type);

    /**
     * @brief This function informs the context that a function is being called.
     *
     * It pushes the function to the function call stack and creates a new set of allocated registers.
     * This is necessary to manage register spillage and restore.
     *
     * @param function The name of the function being called.
     */
    void set_function_call(std::string function);

    /**
     * @brief This function informs the context that a function call has ended.
     *
     * It pops the function from the function call stack and the set of allocated registers.
     * This is necessary to manage register spillage and restore in the parent scope.
     */
    void pop_function_call();

    /**
     * @brief This function returns the function being called.
     *
     * @return The function being called.
     */
    Function get_function_call() const;

    // ============= CONTROL FLOW MANAGEMENT ==============

    /**
     * @brief This function creates a unique label for control flow.
     *
     * This function is static and can be called without an instance of the class. (eg. Context::create_label("while"))
     *
     * @param id The identifier of the label, used to differentiate between while/for/if for clarity.
     * @return The unique label.
     */
    static std::string create_label(std::string id);

    /**
     * @brief This function saves the label pointing to the start of the body in the reserved stack.
     *
     * This function is used to implement CONTINUE statements.
     *
     * @param label The label to save.
     */
    void save_start_label(std::string label);

    /**
     * @brief This function saves the label pointing to the end of the body in the reserved stack.
     *
     * This function is used to implement BREAK statements.
     *
     * @param label The label to save.
     */
    void save_end_label(std::string label);

    /**
     * @brief This function pops the last saved start label from the reserved stack.
     *
     * This function is used to implement CONTINUE statements.
     */
    void pop_start_label();

    /**
     * @brief This function pops the last saved end label from the reserved stack.
     *
     * This function is used to implement BREAK statements.
     */
    void pop_end_label();

    /**
     * @brief This function returns the last saved start label.
     *
     * The stack is not modified. THe latest saved label is fetched as only the innermost loop is affected.
     * This function is used to implement CONTINUE statements.
     *
     * @return The last saved start label.
     */
    std::string get_start_label() const;

    /**
     * @brief This function returns the last saved end label.
     *
     * The stack is not modified. THe latest saved label is fetched as only the innermost loop is affected.
     * This function is used to implement BREAK statements.
     *
     * @return The last saved end label.
     */
    std::string get_end_label() const;

    // ============= STORE, LOAD AND MOVE INSTRUCTIONS ==============

    /**
     * @brief This function returns the move instruction for a given type.
     *
     * @param type The type to move.
     * @return The move instruction for the given type.
     */
    std::string move_instruction(Type type) const;

    /**
     * @brief This function returns the store instruction for a given type.
     *
     * @param type The type to store.
     * @return The store instruction for the given type.
     */
    std::string store_instruction(Type type) const;

    /**
     * @brief This function returns the load instruction for a given type.
     *
     * @param type The type to load.
     * @return The load instruction for the given type.
     */
    std::string load_instruction(Type type) const;

    // ============= OPERATIONS MANAGEMENT ==============

    /**
     * @brief This function sets the type of the last operation being performed.
     *
     * @param type The type of the operation.
     */
    void set_operation_type(Type type);

    /**
     * @brief This function pops the last operation type from the stack.
     */
    void pop_operation_type();

    /**
     * @brief This function returns the type of the last operation being performed.
     *
     * @return The type of the operation.
     */
    Type get_operation_type() const;

    /**
     * @brief Check if an expression is being evaluated
     *
     * This function checks if an expression is being evaluated.
     * To do so, it checks if the operation_type_stack is not empty.
     * It is used within Identifier::EmitRISC to decide whether to load a variable from memory or not.
     *
     * @return True if an expression is being evaluated, false otherwise
     */
    bool evaluating_expression() const;

    // ============= FLOATS AND DOUBLES MANAGEMENT ==============
    /**
     * @brief This function declares a float constant to later be printed by Context::PrintConstant
     *
     * @param value The float value to declare
     * @return The index of the constant in the constant_declarations vector
     */
    int declare_constant(float value);

    /**
     * @brief This function declares a double constant to later be printed by Context::PrintConstant
     *
     * @param value The float value to declare
     * @return The index of the constant in the constant_declarations vector
     */
    int declare_constant(double value);

    /**
     * @brief This function prints all the constant representation of doubles and floats in the assembly file.
     *
     * @param stream The output stream to write to.
     */
    void print_constant_declarations(std::ostream &stream) const;

    // ============= GLOBALS MANAGEMENT ==============

    /**
     * @brief This function defines a global variable in the context.
     *
     * It saves the global to the global bindings map.
     */
    void define_global(std::string identifier, Global &global_specs);

    /**
     * @brief This function allocates space for a global variable in the assembly file.
     *
     * It prints the label of a global (the identifier) and allocates space in memory using the .zero directive.
     */
    void print_global(std::ostream &stream) const;

    // TODO: Add functions to handle enums, structs, typedef, char and strings

private:
    // ============= REGISTER ALLOCATION ==============

    /**
     * @brief The register file.
     *
     * Contains information on registers such as name, type contained and availability
     */
    static std::unordered_map<int, Register> register_file;

    /**
     * @brief The mapping of register names to register numbers.
     *
     * Used in context functions to access the register file.
     */
    static std::unordered_map<std::string, int> register_int_to_name;

    /**
     * @brief Stack of sets of currently used registers.
     *
     * Used in to manage register spillage and restore.
     */
    std::stack<std::set<int>> allocated_registers;

    /**
     * @brief Mapping of register numbers to their stack offsets.
     *
     * Used to keep track of the stack offsets of registers that have been spilled.
     */
    std::unordered_map<int, int> allocated_register_offsets;

    /**
     * @brief This function allocates a register for a variable.
     *
     * This function sets the register as unavailable and assigns the type of the variable to the register.
     * This function is called within the Context::get_register function.
     */
    void allocate_register(std::string reg_name, Type type);

    // ============= VARIABLE MANAGEMENT ==============

    /**
     * @brief The stack of stack offsets.
     *
     * Used to manage the stack offsets of variables in different scopes.
     * Namely used when popping child scopes to go back to old offset.
     */
    std::stack<int> stack_offset;

    /**
     * @brief The stack of variable bindings.
     *
     * Used to manage the variables in different scopes.
     * Ensures a variables defined in a parent scope is not available in a child scope.
     */
    std::vector<VariablesLayer> variable_bindings;

    int total_offset = 0;

    // ============= FUNCTION MANAGEMENT ==============

    /**
     * @brief The mapping of function names to function specifications.
     *
     * Used to store the functions defined in the context.
     * Contains information on return type and parameters.
     */
    std::unordered_map<std::string, Function> function_bindings;

    /**
     * @brief The end statement of the last function defined.
     *
     * Used to store the end statement of the last function defined.
     * This is used to exit the function scope for RETURN statements.
     */
    std::string last_function_end_statement;

    /**
     * @brief The register to store the return value of a function.
     */
    std::string return_register;

    /**
     * @brief Contains stack of the function calls
     *
     * Used when function calls are nested (eg. f(g()) )
     */
    std::stack<std::string> function_call_stack;

    // ============= CONTROL FLOW MANAGEMENT ==============
    /**
     * @brief The counter for the labels.
     *
     * Ensures no two labels are the same.
     */
    static int label_counter;

    /**
     * @brief The stack of start labels.
     *
     * Used to manage the start labels of loops.
     * Used for CONTINUE statements.
     */
    std::stack<std::string> start_labels;

    /**
     * @brief The stack of end labels.
     *
     * Used to manage the end labels of loops.
     * Used for BREAK statements.
     */
    std::stack<std::string> end_labels;

    // ============= OPERATIONS MANAGEMENT ==============
    /**
     * @brief The stack of operation types.
     *
     * Used to manage the types of the operations being performed.
     * Used to determine the type of the result of the operation.
     * Used to determine whether an identifier needs to be fetched from memory.
     */
    std::stack<Type> operation_type_stack;

    // ============= FLOATS AND DOUBLES MANAGEMENT ==============
    /**
     * @brief The counter for the float constants.
     *
     * Ensures no two constants have the same label.
     */
    int constant_declaration_number = 0;

    /**
     * @brief The vector of float and double constants.
     *
     * Used to store the float/double constants declared in the context.
     * Used to print the float/double constants in the assembly file.
     */
    std::vector<ContextConstant> constant_declarations;

    // ============= GLOBALS MANAGEMENT ==============

    /**
     * @brief The mapping of global names to global specifications.
     *
     * Used to store the global variables defined in the context.
     * Contains information on type, array, pointer.
     */
    std::unordered_map<std::string, Global> global_bindings;
};

#endif
