#ifndef CONTEXT_CONSTANT
#define CONTEXT_CONSTANT

#include "context_types.hpp"
#include <iostream>

class ContextConstant
{

private:
    Type type_;
    uint32_t lower_int;
    uint32_t upper_int;

    union FloatRepresentation
    {
        float float_representation;
        uint32_t integer_representation;
    };

    union DoubleRepresentation
    {
        double double_representation;
        struct
        {
            uint32_t lower; // Assuming little-endian
            uint32_t upper;
        } parts;
    };

public:
    ContextConstant(float value)
    {
        type_ = Type::_FLOAT;

        // Convert float to int
        FloatRepresentation representation;
        representation.float_representation = value;
        lower_int = representation.integer_representation;
    }

    ContextConstant(double value)
    {
        type_ = Type::_DOUBLE;

        // Convert double to int
        DoubleRepresentation representation;
        representation.double_representation = value;
        lower_int = representation.parts.lower;
        upper_int = representation.parts.upper;
    }

    void PrintConstant(std::ostream &stream) const;
};

#endif
