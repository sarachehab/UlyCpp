#ifndef CONTEXT_MODE
#define CONTEXT_MODE

enum class Mode
{
    GLOBAL,
    LOCAL,
    ASSIGN,             // For assignments
    LOCAL_DECLARATION,  // For declarations
    GLOBAL_DECLARATION, // For global declarations
    INITIALIZATION,     // For initializations
    SIZEOF,             // For sizeof operator
    OPERATOR,           // For logical, arithmetic and comparaison operations
    DEREFERENCING,      // For dereferencing
    FUNCTION_DEFINITION,
    RETURN,
};

#endif