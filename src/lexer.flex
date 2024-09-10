%option noyywrap

%{
  // Required C includes and external declarations
  extern "C" int fileno(FILE *stream);
  #include "parser.tab.hpp"
  #include <string>
  #include <cstdlib>

  // Function declarations
  void push_back_string(const std::string &s);
  void consume_spaces();
  void process_typedef_and_push_back(TypedefSpec typedef_spec);
%}

D	[0-9]
L	[a-zA-Z_]
H   [a-fA-F0-9]
E	[Ee][+-]?{D}+
FSF (f|F)
FSL (l|L)
IS  (u|U|l|L)*

%%

"auto"          { return AUTO; }
"break"         { return BREAK; }
"case"          { return CASE; }
"char"          { return CHAR; }
"const"         { return CONST; }
"continue"      { return CONTINUE; }
"default"       { return DEFAULT; }
"do"            { return DO; }
"double"        { return DOUBLE; }
"else"          { return ELSE; }
"enum"          { return ENUM; }
"extern"        { return EXTERN; }
"float"         { return FLOAT; }
"for"           { return FOR; }
"goto"          { return GOTO; }
"if"            { return IF; }
"int"           { return INT; }
"long"          { return LONG; }
"register"      { return REGISTER; }
"return"        { return RETURN; }
"short"         { return SHORT; }
"signed"        { return SIGNED; }
"sizeof"        { return SIZEOF; }
"static"        { return STATIC; }
"struct"        { return STRUCT; }
"switch"        { return SWITCH; }
"typedef"       { return TYPEDEF; }
"union"         { return UNION; }
"unsigned"      { return UNSIGNED; }
"void"          { return VOID; }
"volatile"      { return VOLATILE; }
"while"         { return WHILE; }

{L}({L}|{D})* {
    std::string *str = new std::string(yytext);
    if (Context::is_enum(*str)) {
        yylval.number_int = Context::get_enum_value(*str);
        delete str;
        return INT_CONSTANT;
    } else if (Context::is_typedef(*str)) {
        process_typedef_and_push_back(Context::get_typedef_spec(*str));
        delete str;
    } else {
        yylval.string = str;
        return IDENTIFIER;
    }
}

0[xX]{H}+{IS}?		        {yylval.number_int = (int)strtol(yytext, NULL, 0); return(INT_CONSTANT);}
0{D}+{IS}?		            {yylval.number_int = (int)strtol(yytext, NULL, 0); return(INT_CONSTANT);}
{D}+{IS}?		            {yylval.number_int = (int)strtol(yytext, NULL, 0); return(INT_CONSTANT);}
L?'(\\.|[^\\'])+'           {yylval.number_int = yytext[1]; return(INT_CONSTANT);}

{D}+{E}{FSF}?		        {yylval.number_float = strtod(yytext, NULL); return(FLOAT_CONSTANT);}
{D}*"."{D}+({E})?{FSF}?	    {yylval.number_float = strtod(yytext, NULL); return(FLOAT_CONSTANT);}
{D}+"."{D}*({E})?{FSF}?	    {yylval.number_float = strtod(yytext, NULL); return(FLOAT_CONSTANT);}

{D}+{E}{FSL}		        {yylval.number_double = strtod(yytext, NULL); return(DOUBLE_CONSTANT);}
{D}*"."{D}+({E})?{FSL}	    {yylval.number_double = strtod(yytext, NULL); return(DOUBLE_CONSTANT);}
{D}+"."{D}*({E})?{FSL}	    {yylval.number_double = strtod(yytext, NULL); return(DOUBLE_CONSTANT);}


L?'(\\.|[^\\'])' {
    // Process the character literal
    char* characters = Context::process_char(yytext);

    // The result should be a single character
    yylval.character = characters[0];

    delete[] characters;
    return(CHAR_LITERAL);
}

L?\"(\\.|[^\\"])*\" {
    // Process the string literal
    char* characters = Context::process_char(yytext);
    std::string output = Context::preserve_escape_sequences(characters);

    // Create a string from the processed characters
    yylval.string = new std::string(output);

    delete[] characters;
    return(STRING_LITERAL);
}

(\*+&+)+	{
              char* result = Context::cancel_pointer_pairs(yytext);
              if (result[0] != '\0') {
                  // Push the remaining characters back onto the input stream in reverse order
                  for (int i = strlen(result) - 1; i >= 0; i--) {
                      unput(result[i]);
                  }
              }
}

"..."       {return(ELLIPSIS);}
">>="		{return(RIGHT_ASSIGN);}
"<<="       {return(LEFT_ASSIGN);}
"+="		{return(ADD_ASSIGN);}
"-="        {return(SUB_ASSIGN);}
"*="        {return(MUL_ASSIGN);}
"/="		{return(DIV_ASSIGN);}
"%="		{return(MOD_ASSIGN);}
"&="        {return(AND_ASSIGN);}
"^="		{return(XOR_ASSIGN);}
"|="        {return(OR_ASSIGN);}
">>"        {return(RIGHT_OP);}
"<<"        {return(LEFT_OP);}
"++"	    {return(INC_OP);}
"--"	    {return(DEC_OP);}
"->"	    {return(PTR_OP);}
"&&"	    {return(AND_OP);}
"||"	    {return(OR_OP);}
"<="	    {return(LE_OP);}
">="	    {return(GE_OP);}
"=="	    {return(EQ_OP);}
"!="	    {return(NE_OP);}
";"			{return(';');}
("{"|"<%")  {return('{');}
("}"|"%>")  {return('}');}
","		    {return(',');}
":"		    {return(':');}
"="		    {return('=');}
"("		    {return('(');}
")"		    {return(')');}
("["|"<:")  {return('[');}
("]"|":>")  {return(']');}
"."			{return('.');}
"&"			{return('&');}
"!"			{return('!');}
"~"			{return('~');}
"-"			{return('-');}
"+"			{return('+');}
"*"			{return('*');}
"/"			{return('/');}
"%"			{return('%');}
"<"			{return('<');}
">"			{return('>');}
"^"			{return('^');}
"|"			{return('|');}
"?"			{return('?');}

[ \a\b\t\v\f\n\r]		{/* ignore new lines and special sequences */}
.                   {yyerror("Unknown character");}

%%

void yyerror (char const *s)
{
  fprintf(stderr, "Lexing error: %s\n", s);
  exit(1);
}

// Push back a string in reverse order with leading and trailing space
void push_back_string(const std::string &s) {
    consume_spaces(); // Ensure spaces are managed
    for (int i = s.size() - 1; i >= 0; --i) {
        unput(s[i]); // Push characters one by one
    }
    unput(' '); // Add space after string
}

// Consume leading spaces or tabs before processing the next token
void consume_spaces() {
    char next_char;
    while ((next_char = yyinput()) == ' ' || next_char == '\t') {
        // Skip spaces and tabs
    }
    unput(next_char); // Push back first non-space character for later handling
}

// Process a single parameter within a typedef declaration
void process_single_parameter(TypedefSpec typedef_spec, std::vector<std::string>& parameters, std::vector<int>& pointer_counts, std::vector<char>& separators) {
    char next_char;
    std::string variable_name = "";

    // Capture variable name until we hit a ',', ';', '(', or ')'
    while ((next_char = yyinput()) != ',' && next_char != ';' && next_char != '(' && next_char != ')') {
        variable_name += next_char;
    }

    // Store the trimmed variable name, pointer count, and separator
    parameters.push_back(variable_name);
    pointer_counts.push_back(typedef_spec.number_pointers_);
    separators.push_back(next_char);

    // If a comma is encountered, recursively process the next parameter
    if (next_char == ',') {
        process_single_parameter(typedef_spec, parameters, pointer_counts, separators);
    }
}

// Process typedef and push back all parameters and types
void process_typedef_and_push_back(TypedefSpec typedef_spec) {
    std::vector<std::string> parameters; // Store parameter names
    std::vector<int> pointer_counts;     // Store pointer counts
    std::vector<char> separators;        // Store separators (e.g., ',', ';', etc.)

    // Recursively process each parameter
    process_single_parameter(typedef_spec, parameters, pointer_counts, separators);

    // Push back parameters in reverse order
    for (int i = parameters.size() - 1; i >= 0; --i) {
        unput(' ');
        unput(separators[i]);  // Push the separator character
        push_back_string(parameters[i]);
        unput(' ');

        // Push back any pointer symbols ('*' or '&')
        int number_pointers = pointer_counts[i];
        if (number_pointers > 0) {
            for (int j = 0; j < number_pointers; ++j) {
                unput('*');
            }
        } else if (number_pointers < 0) {
            for (int j = 0; j > number_pointers; --j) {
                unput('&');
            }
        }
        unput(' ');
    }

    // Push back the type string at the end
    std::string type;

    switch (typedef_spec.type_) {
        case Type::_CHAR: type = "char "; break;
        case Type::_SHORT: type = "short "; break;
        case Type::_UNSIGNED_INT: type = "unsigned int "; break;
        case Type::_INT: type = "int "; break;
        case Type::_LONG: type = "long "; break;
        case Type::_FLOAT: type = "float "; break;
        case Type::_DOUBLE: type = "double "; break;
        case Type::_STRUCT: type = "struct " + typedef_spec.base_class_ + " "; break;
        default: throw std::runtime_error("Lexer - Typedef unrecognized type");
    }

    push_back_string(type);  // Push back the type
}
