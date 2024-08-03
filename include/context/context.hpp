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

class Context
{

public:
    Context();
    ~Context();

    // Register allocation
    std::string get_register(Type type);
    std::string get_return_register() const;
    void allocate_register(std::string reg_name, Type type);
    void deallocate_register(std::string reg_name);
    std::string get_register_name(int reg_number) const;
    void set_register_type(std::string reg_name, Type type);
    void add_register_to_set(std::string reg_name);
    void remove_register_from_set(std::string reg_name);

    // Register saving for function calls
    void push_registers(std::ostream &stream);
    void pop_registers(std::ostream &stream);

    // Stack management
    void create_new_scope();
    void pop_scope();
    int get_stack_offset() const;
    void increase_stack_offset(int offset);

    // Variable management
    void define_variable(std::string identifier, Variable variable);
    Variable get_variable(std::string identifier) const;

    // Function management
    void define_function(std::string identifier, Function function);
    Function get_function(std::string identifier) const;
    std::string get_last_function_end_statement() const;
    void exit_function();
    void set_return_register(Type type);
    void set_function_call(std::string function);
    void pop_function_call();
    Function get_function_call() const;

    // Label creation for control flow
    std::string create_label(std::string id);

    // Label saving and fetching for control flow
    void save_start_label(std::string label);
    void save_end_label(std::string label);
    void pop_start_label();
    void pop_end_label();
    std::string get_start_label() const;
    std::string get_end_label() const;

    // Move, store and load instructions
    std::string move_instruction(Type type) const;
    std::string store_instruction(Type type) const;
    std::string load_instruction(Type type) const;

    // Type management
    void set_operation_type(Type type);
    void pop_operation_type();
    Type get_operation_type() const;

    // Operation instructions
    bool evaluating_expression() const;

    // Constant declarations
    int declare_constant(float value);
    int declare_constant(double value);
    void print_constant_declarations(std::ostream &stream) const;

    // TODO: Add functions to handle enums, structs, typedef, char and strings

private:
    // Register file
    static std::unordered_map<int, Register> register_file;
    static std::unordered_map<std::string, int> register_int_to_name;
    std::stack<std::set<int>> allocated_registers;
    std::unordered_map<int, int> allocated_register_offsets;

    // Variable map
    std::stack<int> stack_offset;
    std::vector<VariablesLayer> variable_bindings;

    // Function map
    std::unordered_map<std::string, Function> function_bindings;
    std::string last_function_end_statement;
    std::string return_register;
    std::stack<std::string> function_call_stack;

    // Control flow labels
    int label_counter;
    std::stack<std::string> start_labels;
    std::stack<std::string> end_labels;

    // Type tracking
    std::stack<Type> operation_type_stack;

    // Constant declarations
    int constant_declaration_number = 0;
    std::vector<ContextConstant> constant_declarations;
};

#endif
