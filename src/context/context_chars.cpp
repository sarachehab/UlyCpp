#include "../../include/context/context.hpp"

void ContextStrings::PrintString(std::ostream &stream) const
{
    stream << "string_" << label_number_ << ":" << std::endl;
    stream << "\t.string \"" << value_ << "\"" << std::endl;
}

int Context::define_string(std::string value)
{
    string_declarations.push_back(ContextStrings(string_declaration_number, value));
    return string_declaration_number++;
}

void Context::print_string_declarations(std::ostream &stream) const
{
    for (const auto &declaration : string_declarations)
    {
        declaration.PrintString(stream);
    }
}
