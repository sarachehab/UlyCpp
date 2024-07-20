#include "../../include/context/context.hpp"

// Initialize register file
std::unordered_map<int, Register> Context::register_file = {
    {0, Register(false, SpecifierType::_INT, "zero")},
    {1, Register(false, SpecifierType::_INT, "ra")},
    {2, Register(false, SpecifierType::_INT, "sp")},
    {3, Register(false, SpecifierType::_INT, "gp")},
    {4, Register(false, SpecifierType::_INT, "tp")},
    {5, Register(true, SpecifierType::_INT, "t0")},
    {6, Register(true, SpecifierType::_INT, "t1")},
    {7, Register(true, SpecifierType::_INT, "t2")},
    {8, Register(false, SpecifierType::_INT, "s0")}, // or fp
    {9, Register(false, SpecifierType::_INT, "s1")},
    {10, Register(false, SpecifierType::_INT, "a0")},
    {11, Register(false, SpecifierType::_INT, "a1")},
    {12, Register(false, SpecifierType::_INT, "a2")},
    {13, Register(false, SpecifierType::_INT, "a3")},
    {14, Register(false, SpecifierType::_INT, "a4")},
    {15, Register(false, SpecifierType::_INT, "a5")},
    {16, Register(false, SpecifierType::_INT, "a6")},
    {17, Register(false, SpecifierType::_INT, "a7")},
    {18, Register(false, SpecifierType::_INT, "s2")},
    {19, Register(false, SpecifierType::_INT, "s3")},
    {20, Register(false, SpecifierType::_INT, "s4")},
    {21, Register(false, SpecifierType::_INT, "s5")},
    {22, Register(false, SpecifierType::_INT, "s6")},
    {23, Register(false, SpecifierType::_INT, "s7")},
    {24, Register(false, SpecifierType::_INT, "s8")},
    {25, Register(false, SpecifierType::_INT, "s9")},
    {26, Register(false, SpecifierType::_INT, "s10")},
    {27, Register(false, SpecifierType::_INT, "s11")},
    {28, Register(true, SpecifierType::_INT, "t3")},
    {29, Register(true, SpecifierType::_INT, "t4")},
    {30, Register(true, SpecifierType::_INT, "t5")},
    {31, Register(true, SpecifierType::_INT, "t6")},
    {32, Register(true, SpecifierType::_FLOAT, "ft0")},
    {33, Register(true, SpecifierType::_FLOAT, "ft1")},
    {34, Register(true, SpecifierType::_FLOAT, "ft2")},
    {35, Register(true, SpecifierType::_FLOAT, "ft3")},
    {36, Register(true, SpecifierType::_FLOAT, "ft4")},
    {37, Register(true, SpecifierType::_FLOAT, "ft5")},
    {38, Register(true, SpecifierType::_FLOAT, "ft6")},
    {39, Register(true, SpecifierType::_FLOAT, "ft7")},
    {40, Register(false, SpecifierType::_FLOAT, "fs0")},
    {41, Register(false, SpecifierType::_FLOAT, "fs1")},
    {42, Register(false, SpecifierType::_FLOAT, "fa0")},
    {43, Register(false, SpecifierType::_FLOAT, "fa1")},
    {44, Register(true, SpecifierType::_FLOAT, "fa2")},
    {45, Register(true, SpecifierType::_FLOAT, "fa3")},
    {46, Register(true, SpecifierType::_FLOAT, "fa4")},
    {47, Register(true, SpecifierType::_FLOAT, "fa5")},
    {48, Register(true, SpecifierType::_FLOAT, "fa6")},
    {49, Register(true, SpecifierType::_FLOAT, "fa7")},
    {50, Register(true, SpecifierType::_FLOAT, "fs2")},
    {51, Register(true, SpecifierType::_FLOAT, "fs3")},
    {52, Register(true, SpecifierType::_FLOAT, "fs4")},
    {53, Register(true, SpecifierType::_FLOAT, "fs5")},
    {54, Register(true, SpecifierType::_FLOAT, "fs6")},
    {55, Register(true, SpecifierType::_FLOAT, "fs7")},
    {56, Register(true, SpecifierType::_FLOAT, "fs8")},
    {57, Register(true, SpecifierType::_FLOAT, "fs9")},
    {58, Register(true, SpecifierType::_FLOAT, "fs10")},
    {59, Register(true, SpecifierType::_FLOAT, "fs11")},
    {60, Register(false, SpecifierType::_FLOAT, "ft8")},
    {61, Register(false, SpecifierType::_FLOAT, "ft9")},
    {62, Register(false, SpecifierType::_FLOAT, "ft10")},
    {63, Register(false, SpecifierType::_FLOAT, "ft11")}};

// Map register name to register number
std::unordered_map<std::string, int> register_name_to_int = {
    {"zero", 0},
    {"ra", 1},
    {"sp", 2},
    {"gp", 3},
    {"tp", 4},
    {"t0", 5},
    {"t1", 6},
    {"t2", 7},
    {"s0", 8},
    {"s1", 9},
    {"a0", 10},
    {"a1", 11},
    {"a2", 12},
    {"a3", 13},
    {"a4", 14},
    {"a5", 15},
    {"a6", 16},
    {"a7", 17},
    {"s2", 18},
    {"s3", 19},
    {"s4", 20},
    {"s5", 21},
    {"s6", 22},
    {"s7", 23},
    {"s8", 24},
    {"s9", 25},
    {"s10", 26},
    {"s11", 27},
    {"t3", 28},
    {"t4", 29},
    {"t5", 30},
    {"t6", 31},
    {"ft0", 32},
    {"ft1", 33},
    {"ft2", 34},
    {"ft3", 35},
    {"ft4", 36},
    {"ft5", 37},
    {"ft6", 38},
    {"ft7", 39},
    {"fs0", 40},
    {"fs1", 41},
    {"fa0", 42},
    {"fa1", 43},
    {"fa2", 44},
    {"fa3", 45},
    {"fa4", 46},
    {"fa5", 47},
    {"fa6", 48},
    {"fa7", 49},
    {"fs2", 50},
    {"fs3", 51},
    {"fs4", 52},
    {"fs5", 53},
    {"fs6", 54},
    {"fs7", 55},
    {"fs8", 56},
    {"fs9", 57},
    {"fs10", 58},
    {"fs11", 59},
    {"ft8", 60},
    {"ft9", 61},
    {"ft10", 62},
    {"ft11", 63}};

std::string Context::get_register(SpecifierType type)
{
    int start_register_file;
    switch (type)
    {
    case SpecifierType::_INT:
    case SpecifierType::_CHAR:
    case SpecifierType::_SHORT:
    case SpecifierType::_UNSIGNED_INT:
        start_register_file = 5;
        break;
    case SpecifierType::_FLOAT:
    case SpecifierType::_DOUBLE:
    case SpecifierType::_LONG:
        start_register_file = 32;
        break;
    default:
        throw std::runtime_error("Context::get_register: Invalid variable type");
    }

    for (int i = start_register_file; i < 64; i++)
    {
        if (register_file[i].is_available)
        {
            allocate_register(register_file[i].name, type);
            return register_file[i].name;
        }
    }
    throw std::runtime_error("Context::get_register: No available register");
}

// Get the return register of the given type
std::string Context::get_return_register(SpecifierType type)
{
    switch (type)
    {
    case SpecifierType::_INT:
    case SpecifierType::_CHAR:
    case SpecifierType::_SHORT:
    case SpecifierType::_UNSIGNED_INT:
        return "a0";
    case SpecifierType::_FLOAT:
    case SpecifierType::_DOUBLE:
    case SpecifierType::_LONG:
        return "fa0";
    case SpecifierType::_VOID:
        throw std::runtime_error("Context::get_return_register: VOID not supported");
    default:
        throw std::runtime_error("Context::get_return_register: Invalid return type");
    }
}

// Allocate a register of the given type
void Context::allocate_register(std::string reg_name, SpecifierType type)
{
    int reg = register_name_to_int[reg_name];
    register_file[reg].is_available = false;
    register_file[reg].type = type;
    allocated_registers.insert(reg);
}

// Deallocate a register
void Context::deallocate_register(std::string reg_name)
{
    int reg = register_name_to_int[reg_name];
    // Future Scopes: Add store instruction here
    register_file[reg].is_available = true;
    allocated_registers.erase(reg);
}

// TODO
void Context::push_registers()
{
    for (int reg : allocated_registers)
    {
        // Future Scopes: Add load instruction here
        SpecifierType type = register_file[reg].type;
        std::cout << store_instruction(type) << std::endl;
    }
}

// TODO
void Context::pop_registers()
{
    for (int reg : allocated_registers)
    {
        // Future Scopes: Add load instruction here
        SpecifierType type = register_file[reg].type;
        std::cout << load_instruction(type) << std::endl;
    }
}