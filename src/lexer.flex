%option noyywrap

%{
  // A lot of this lexer is based off the ANSI C grammar:
  // https://www.lysator.liu.se/c/ANSI-C-grammar-l.html#MUL-ASSIGN
  // Avoid error "error: `fileno' was not declared in this scope"
  extern "C" int fileno(FILE *stream);

  #include "parser.tab.hpp"

%}

D	[0-9]
L	[a-zA-Z_]
H   [a-fA-F0-9]
E	[Ee][+-]?{D}+
FSF (f|F)
FSL (l|L)
IS  (u|U|l|L)*

%%
"/*"			{/* consumes comment - TODO you might want to process and emit it in your assembly for debugging */}

"auto"			{return(AUTO);}
"break"			{return(BREAK);}
"case"			{return(CASE);}
"char"			{return(CHAR);}
"const"			{return(CONST);}
"continue"      {return(CONTINUE);}
"default"		{return(DEFAULT);}
"do"			{return(DO);}
"double"		{return(DOUBLE);}
"else"			{return(ELSE);}
"enum"			{return(ENUM);}
"extern"		{return(EXTERN);}
"float"			{return(FLOAT);}
"for"			{return(FOR);}
"goto"			{return(GOTO);}
"if"			{return(IF);}
"int"			{return(INT);}
"long"			{return(LONG);}
"register"	    {return(REGISTER);}
"return"		{return(RETURN);}
"short"			{return(SHORT);}
"signed"		{return(SIGNED);}
"sizeof"		{return(SIZEOF);}
"static"		{return(STATIC);}
"struct"		{return(STRUCT);}
"switch"		{return(SWITCH);}
"typedef"		{return(TYPEDEF);}
"union"			{return(UNION);}
"unsigned"	    {return(UNSIGNED);}
"void"			{return(VOID);}
"volatile"	    {return(VOLATILE);}
"while"			{return(WHILE);}

{L}({L}|{D})*		        { std::string *str = new std::string(yytext); if (Context::is_enum(*str)) { yylval.number_int = Context::get_enum_value(*str); delete str; return (INT_CONSTANT); } else if(Context::is_typedef(*str)) { yylval.string = str; return (TYPE_NAME); } yylval.string = str; return(IDENTIFIER); }

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
