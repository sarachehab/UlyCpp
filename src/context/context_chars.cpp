#include "../../include/context/context.hpp"

void ContextStrings::PrintString(std::ostream &stream) const
{
    stream << "string_" << label_number_ << ":" << std::endl;
    stream << "\t.string \"" << value_ << "\"" << std::endl;
}

char *Context::process_char(const char *sequence)
{
    // Determine the length of the sequence, excluding the enclosing single quotes
    size_t length = strlen(sequence);

    // Allocate memory for the result (excluding the quotes and null terminator)
    char *result = new char[length - 1];

    size_t result_index = 0;

    for (size_t i = 1; i < length - 1; ++i) // Skip the first and last characters (' and ')
    {
        if (sequence[i] == '\\') // Handle escape sequences
        {
            auto it = special_char_sequences.find(sequence[i + 1]);
            if (it != special_char_sequences.end())
            {
                result[result_index++] = it->second;
                ++i; // Skip the next character since it's part of the escape sequence
            }
            else
            {
                delete[] result; // Clean up memory if an error occurs
                throw std::runtime_error("Context::process_char - Invalid escape sequence");
            }
        }
        else // Handle regular characters
        {
            result[result_index++] = sequence[i];
        }
    }

    // Null-terminate the result
    result[result_index] = '\0';

    return result; // Return the pointer to the processed characters
}

std::string Context::preserve_escape_sequences(const char *processed_characters)
{
    std::string result;

    for (size_t i = 0; processed_characters[i] != '\0'; ++i)
    {
        bool found = false;

        // Iterate through the map to find the matching escape sequence
        for (const auto &pair : special_char_sequences)
        {
            if (processed_characters[i] == pair.second)
            {
                result.push_back('\\');
                result.push_back(pair.first);
                found = true;
                break;
            }
        }

        // If the character wasn't found in the map, add it as-is
        if (!found)
        {
            result.push_back(processed_characters[i]);
        }
    }

    return result;
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
