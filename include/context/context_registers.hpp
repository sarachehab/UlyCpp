#ifndef CONTEXT_REGISTERS
#define CONTEXT_REGISTERS

struct Register
{
    bool is_available;
    SpecifierType type;
    std::string name;

    Register() : is_available(false), type(SpecifierType::_VOID), name("") {}
    Register(bool is_available, SpecifierType type, std::string name) : is_available(is_available), type(type), name(name) {}
};

#endif