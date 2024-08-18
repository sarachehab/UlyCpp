#ifndef CONTEXT_CHARS_HPP
#define CONTEXT_CHARS_HPP

#include <unordered_map>

class ContextStrings
{
private:
    int label_number_;
    std::string value_;

public:
    ContextStrings() {}
    ContextStrings(int label_number, std::string value) : label_number_(label_number), value_(value) {};
    ~ContextStrings() {}

    void PrintString(std::ostream &stream) const;
};

const std::unordered_map<char, char> special_char_sequences = {
    {'a', '\007'}, // Bell/alert
    {'b', '\b'},   // Backspace
    {'e', '\033'}, // Escape
    {'f', '\f'},   // Form feed
    {'n', '\n'},   // Newline
    {'r', '\r'},   // Carriage return
    {'t', '\t'},   // Horizontal tab
    {'v', '\013'}, // Vertical tab
    {'0', '\0'},   // Null character
    {'\\', '\\'},  // Backslash
    {'\'', '\''},  // Single quote
    {'"', '\"'},   // Double quote
    {'?', '\?'}    // Question mark
};

#endif
