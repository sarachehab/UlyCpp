#ifndef CONTEXT_CONSTANT
#define CONTEXT_CONSTANT

#include "context_types.hpp"
#include "context_conversion.hpp"
#include <iostream>

/**
 * @brief This class represents a constant in the context.
 *
 * This class is used to store constants in the context.
 * It is used to store float and double constants.
 */
class ContextConstant
{

private:
    Type type_;
    uint32_t lower_int;
    uint32_t upper_int;

public:
    /**
     * @brief This constructor initializes a float constant.
     *
     * @param value The value of the constant.
     */
    ContextConstant(float value)
    {
        type_ = Type::_FLOAT;

        // Convert float to int
        FloatRepresentation representation;
        representation.float_representation = value;
        lower_int = representation.integer_representation;
    }

    /**
     * @brief This constructor initializes a double constant.
     *
     * @param value The value of the constant.
     */
    ContextConstant(double value)
    {
        type_ = Type::_DOUBLE;

        // Convert double to int
        DoubleRepresentation representation;
        representation.double_representation = value;
        lower_int = representation.parts.lower;
        upper_int = representation.parts.upper;
    }

    /**
     * @brief This function prints the constant representation of an individual double or float in the assembly file.
     *
     * @param stream The output stream to write to.
     */
    void PrintConstant(std::ostream &stream) const;

    /**
     * @brief This function returns the type of the constant.
     */
    Type GetType() const;
};

#endif
