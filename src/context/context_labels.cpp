#include "../../include/context/context.hpp"

std::string Context::create_label(std::string label)
{
    return label + std::to_string(label_counter++);
}

void Context::save_start_label(std::string label)
{
    start_labels.push(label);
}

void Context::save_end_label(std::string label)
{
    end_labels.push(label);
}

void Context::pop_start_label()
{
    start_labels.pop();
}

void Context::pop_end_label()
{
    end_labels.pop();
}

std::string Context::get_start_label() const
{
    return start_labels.top();
}

std::string Context::get_end_label() const
{
    return end_labels.top();
}
