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
#include "context_mode.hpp"

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

    // Register saving for function calls
    void push_registers();
    void pop_registers();

    // Stack management
    void create_new_scope();
    void pop_scope();
    int get_stack_offset() const;
    void increase_stack_offset(int offset);
    void set_initial_offset(int offset);

    // Variable management
    void define_variable(std::string identifier, Variable variable);
    Variable get_variable(std::string identifier) const;

    // Function management
    void define_function(std::string identifier, Function function);
    Function get_function(std::string identifier) const;
    std::string get_last_function_end_statement() const;
    void set_return_register(Type type);

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

    // Mode management
    void mode_push(Mode mode);
    void mode_pop();
    bool has_mode(Mode mode) const;

    // Type management
    void set_operation_type(Type type);
    void pop_operation_type();
    Type get_operation_type() const;

    // TODO: Add functions to handle enums, structs, typedef, char and strings

    // Type specific properties
    static const std::unordered_map<Type, int> types_size;
    static const std::unordered_map<Type, std::string> assembler_directives;

private:
    // Register file
    static std::unordered_map<int, Register> register_file;
    static std::unordered_map<std::string, int> register_int_to_name;
    std::set<int> allocated_registers;

    // Variable map
    int current_stack_offset;
    int initial_stack_offset;
    std::vector<VariablesLayer> variable_bindings;

    // Function map
    std::unordered_map<std::string, Function> function_bindings;
    std::string last_function_end_statement;
    std::string return_register;

    // Control flow labels
    int label_counter;
    std::stack<std::string> start_labels;
    std::stack<std::string> end_labels;

    // Mode tracking
    std::stack<Mode> mode_stack;

    // Type tracking
    std::stack<Type> operation_type_stack;
};

#endif
