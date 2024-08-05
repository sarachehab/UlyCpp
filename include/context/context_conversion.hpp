#ifndef CONTEXT_CONVERSION_HPP
#define CONTEXT_CONVERSION_HPP

/**
 * @brief This union is used to convert between float and int.
 */
union FloatRepresentation
{
    float float_representation;
    uint32_t integer_representation;
};

/**
 * @brief This union is used to convert between double and int.
 *
 * It assumes little-endian representation.
 */
union DoubleRepresentation
{
    double double_representation;
    struct
    {
        uint32_t lower; // Assuming little-endian
        uint32_t upper;
    } parts;
};

#endif
