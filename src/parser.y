// Adapted from: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

// TODO: you can either continue adding to this grammar file or
// rename parser_full.y to parser.y once you're happy with
// how this example works.

%code requires{
    #include "ast.hpp"

    extern Node *g_root;
    extern FILE *yyin;
    int yylex(void);
    void yyerror(const char *);
	int yylex_destroy(void);
}

// Represents the value associated with any kind of AST node.
%union{
	Node         	*node;
	NodeList     	*nodes;
	int         	number_int;
	float       	number_float;
	double			number_double;
	std::string  	*string;
	yytokentype  	token;
}

%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL DOUBLE_CONSTANT
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token TYPE_NAME TYPEDEF EXTERN STATIC AUTO REGISTER SIZEOF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <node> translation_unit external_declaration function_definition primary_expression postfix_expression argument_expression_list
%type <node> unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression
%type <node> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> conditional_expression assignment_expression expression constant_expression declaration declaration_specifiers init_declarator_list
%type <node> init_declarator type_specifier struct_specifier struct_declaration_list struct_declaration specifier_qualifier_list struct_declarator_list
%type <node> struct_declarator enum_specifier enumerator_list enumerator declarator direct_declarator pointer parameter_list parameter_declaration
%type <node> identifier_list type_name abstract_declarator direct_abstract_declarator initializer initializer_list statement labeled_statement
%type <node> compound_statement declaration_list expression_statement selection_statement iteration_statement jump_statement

%type <nodes> statement_list

%type <string> unary_operator assignment_operator storage_class_specifier

%type <number_int> INT_CONSTANT STRING_LITERAL
%type <number_float> FLOAT_CONSTANT
%type <number_double> DOUBLE_CONSTANT
%type <string> IDENTIFIER


%start ROOT
%%

ROOT
    : translation_unit { g_root = $1; }

translation_unit
	: external_declaration 						{ $$ = new NodeList($1); }
	| translation_unit external_declaration		{ NodeList *translation_unit = dynamic_cast<NodeList *>($1); translation_unit->PushBack($2); $$ = translation_unit; }
	;

external_declaration
	: function_definition 	{ $$ = $1; }
	| declaration 			{ $$ = $1; }
	;

function_definition
	: declaration_specifiers declarator compound_statement { $$ = new FunctionDefinition($1, $2, $3); }
	;

declaration_specifiers
	: type_specifier { $$ = $1; }
	;

type_specifier
	: INT 		{ $$ = new TypeSpecifier(Type::_INT); }
	| FLOAT 	{ $$ = new TypeSpecifier(Type::_FLOAT); }
	| DOUBLE 	{ $$ = new TypeSpecifier(Type::_DOUBLE); }
	| CHAR 		{ $$ = new TypeSpecifier(Type::_CHAR); }
	| UNSIGNED 	{ $$ = new TypeSpecifier(Type::_UNSIGNED_INT); }
	| SHORT 	{ $$ = new TypeSpecifier(Type::_SHORT); }
	;

declarator
	: direct_declarator { $$ = $1; }
	;

direct_declarator
	: IDENTIFIER                					{ $$ = new Identifier($1); }
	| direct_declarator '(' ')' 					{ $$ = new DirectDeclarator($1); }
	| direct_declarator '(' parameter_list ')'		{ $$ = new DirectDeclarator($1, $3); }
	;

parameter_list
	: parameter_declaration						{ $$ = new ParameterList($1); }
	| parameter_list ',' parameter_declaration	{ ParameterList *parameter_list = dynamic_cast<ParameterList *>($1); parameter_list->PushBack($3); $$ = parameter_list; }
	;

parameter_declaration
	: declaration_specifiers declarator			{ $$ = new ParameterDeclaration($1, $2); }
	;

statement
	: compound_statement 	{ $$ = new CompoundStatement($1); }
	| expression_statement 	{ $$ = $1; }
	| jump_statement 		{ $$ = $1; }
	| selection_statement 	{ $$ = $1; }
	| iteration_statement	{ $$ = $1; }
	;

compound_statement
	: '{' declaration_list '}' 					{ $$ = new CompoundStatement($2); }
	| '{' declaration_list statement_list '}' 	{ CompoundStatement *compound_statement = new CompoundStatement($2); compound_statement->PushBack($3); $$ = compound_statement; }
	| '{' statement_list '}' 					{ $$ = new CompoundStatement($2); }
	| '{' '}' 									{ $$ = new CompoundStatement(nullptr); }
	;

statement_list
	: statement                 { $$ = new StatementList($1); }
	| statement_list statement  { StatementList *statement_list = dynamic_cast<StatementList *>($1); statement_list->PushBack($2); $$ = statement_list; }
	;

jump_statement
	: RETURN ';'            { $$ = new ReturnStatement(nullptr); }
	| RETURN expression ';' { $$ = new ReturnStatement($2); }
	;

primary_expression
	: INT_CONSTANT 			{ $$ = new IntConstant($1); }
	| DOUBLE_CONSTANT		{ $$ = new DoubleConstant($1); }
	| FLOAT_CONSTANT		{ $$ = new FloatConstant($1); }
	| IDENTIFIER			{ $$ = new Identifier($1); }
	| '(' expression ')'	{ $$ = $2; }
	;

expression_statement
	: ';' 				{ $$ = new NodeList(nullptr); }
	| expression ';'	{ $$ = $1; }
	;

postfix_expression
	: primary_expression
	| postfix_expression INC_OP									{ Identifier* identifier_ = dynamic_cast<Identifier *>($1); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); $$ = new PostfixIncrement(identifier_, new Addition(operator_, new IntConstant(1))); }
	| postfix_expression DEC_OP									{ Identifier* identifier_ = dynamic_cast<Identifier *>($1); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); $$ = new PostfixIncrement(identifier_, new Substraction(operator_, new IntConstant(1))); }
	| postfix_expression '(' ')' 								{ $$ = new FunctionCall($1); }
	| postfix_expression '(' argument_expression_list ')'		{ $$ = new FunctionCall($1, $3); }
	;

argument_expression_list
	: assignment_expression									{ $$ = new ExpressionList($1); }
	| argument_expression_list ',' assignment_expression	{ ExpressionList *expression_list = dynamic_cast<ExpressionList *>($1); expression_list->PushBack($3); $$ = expression_list; }
	;

unary_expression
	: postfix_expression
	| '+' cast_expression		{ $$ = $2; }
	| '-' cast_expression		{ $$ = new Negate($2); }
	| '~' cast_expression		{ $$ = new OneComplement($2); }
	| '!' cast_expression		{ $$ = new Inverse($2); }
	| INC_OP unary_expression	{ Identifier* identifier_ = dynamic_cast<Identifier *>($2); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); $$ = new Prefixincrement(identifier_, new Addition(operator_, new IntConstant(1))); }
	| DEC_OP unary_expression	{ Identifier* identifier_ = dynamic_cast<Identifier *>($2); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); $$ = new Prefixincrement(identifier_, new Substraction(operator_, new IntConstant(1))); }
	;

cast_expression
	: unary_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression	{ $$ = new Multiplication($1, $3); }
	| multiplicative_expression '/' cast_expression { $$ = new Division($1, $3); }
	| multiplicative_expression '%' cast_expression { $$ = new Modulus($1, $3); }
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression	{ $$ = new Addition($1, $3); }
	| additive_expression '-' multiplicative_expression	{ $$ = new Substraction($1, $3); }
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression		{ $$ = new LeftShift($1, $3); }
	| shift_expression RIGHT_OP additive_expression 	{ $$ = new RightShift($1, $3); }
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression	{ $$ = new LessThan($1, $3); }
	| relational_expression '>' shift_expression	{ $$ = new LessThan($3, $1); }
	| relational_expression LE_OP shift_expression	{ LessThan *greater_than = new LessThan($3, $1); $$ = new Inverse(greater_than); }
	| relational_expression GE_OP shift_expression	{ LessThan *less_than = new LessThan($1, $3); $$ = new Inverse(less_than); }
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression	{ $$ = new EqualityCheck($1, $3);}
	| equality_expression NE_OP relational_expression	{ EqualityCheck *equality = new EqualityCheck($1, $3); $$ = new Inverse(equality); }
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression	{ $$ = new BitwiseAnd($1, $3); }
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression	{ $$ = new ExclusiveOr($1, $3); }
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression	{ $$ = new InclusiveOr($1, $3); }
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression	{ $$ = new LogicalAnd($1, $3); }
	;

logical_or_expression
	: logical_and_expression
	| logical_and_expression OR_OP inclusive_or_expression	{ $$ = new LogicalOr($1, $3); }
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression	{ $$ = new InlineIf(new ConditionEvaluation($1), $3, $5); }
	;

assignment_expression
	: conditional_expression
	| unary_expression '=' assignment_expression			{ $$ = new Assignment($1, $3); }
	| unary_expression MUL_ASSIGN assignment_expression		{ Identifier* identifier_ = dynamic_cast<Identifier *>($1); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); Multiplication *multiplication = new Multiplication(operator_, $3); $$ = new Assignment(identifier_, multiplication); }
	| unary_expression DIV_ASSIGN assignment_expression		{ Identifier* identifier_ = dynamic_cast<Identifier *>($1); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); Division *division = new Division(operator_, $3); $$ = new Assignment(identifier_, division); }
	| unary_expression MOD_ASSIGN assignment_expression		{ Identifier* identifier_ = dynamic_cast<Identifier *>($1); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); Modulus *modulus = new Modulus(operator_, $3); $$ = new Assignment(identifier_, modulus); }
	| unary_expression ADD_ASSIGN assignment_expression		{ Identifier* identifier_ = dynamic_cast<Identifier *>($1); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); Addition *addition = new Addition(operator_, $3); $$ = new Assignment(identifier_, addition); }
	| unary_expression SUB_ASSIGN assignment_expression		{ Identifier* identifier_ = dynamic_cast<Identifier *>($1); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); Substraction *substraction = new Substraction(operator_, $3); $$ = new Assignment(identifier_, substraction); }
	| unary_expression LEFT_ASSIGN assignment_expression	{ Identifier* identifier_ = dynamic_cast<Identifier *>($1); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); LeftShift *left_shift = new LeftShift(operator_, $3); $$ = new Assignment(identifier_, left_shift); }
	| unary_expression RIGHT_ASSIGN assignment_expression	{ Identifier* identifier_ = dynamic_cast<Identifier *>($1); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); RightShift *right_shift = new RightShift(operator_, $3); $$ = new Assignment(identifier_, right_shift); }
	| unary_expression AND_ASSIGN assignment_expression		{ Identifier* identifier_ = dynamic_cast<Identifier *>($1); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); LogicalAnd *and_op = new LogicalAnd(operator_, $3); $$ = new Assignment(identifier_, and_op); }
	| unary_expression XOR_ASSIGN assignment_expression		{ Identifier* identifier_ = dynamic_cast<Identifier *>($1); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); ExclusiveOr *xor_op = new ExclusiveOr(operator_, $3); $$ = new ExclusiveOr(identifier_, xor_op); }
	| unary_expression OR_ASSIGN assignment_expression		{ Identifier* identifier_ = dynamic_cast<Identifier *>($1); Identifier *operator_ = new Identifier(new std::string(identifier_->GetIdentifier())); LogicalOr *or_op = new LogicalOr(operator_, $3); $$ = new Assignment(identifier_, or_op); }
	;

expression
	: assignment_expression					{ $$ = new Expression($1); }
	| expression ',' assignment_expression	{ Expression *expression_list = dynamic_cast<Expression *>($1); expression_list->PushBack($3); $$ = expression_list; }
	;

declaration
	: declaration_specifiers init_declarator_list ';'	{ $$ = new Declaration($1, $2); }
	;

init_declarator_list
	: init_declarator							{ $$ = new NodeList($1); }
	| init_declarator_list ',' init_declarator	{ NodeList *declarator_list = dynamic_cast<NodeList *>($1); declarator_list->PushBack($3); $$ = declarator_list; }
	;

init_declarator
	: declarator
	| declarator '=' initializer	{ $$ = new Assignment($1, $3); }
	;

initializer
	: assignment_expression
	;

initializer_list
	: initializer						{ $$ = new NodeList($1); }
	| initializer_list ',' initializer	{ $1->PushBack($3); $$ = $1; }
	;

declaration_list
	: declaration					{ $$ = new DeclarationList($1); }
	| declaration_list declaration	{ DeclarationList *declaration_list = dynamic_cast<DeclarationList *>($1); declaration_list->PushBack($2); $$ = declaration_list; }
	;

selection_statement
	: IF '(' expression ')' statement					{ $$ = new IfElse(new ConditionEvaluation($3), $5); }
	| IF '(' expression ')' statement ELSE statement	{ $$ = new IfElse(new ConditionEvaluation($3), $5, $7); }
	;

iteration_statement
	: WHILE '(' expression ')' statement											{ $$ = new WhileLoop(new ConditionEvaluation($3), $5); }
	| FOR '(' expression_statement expression_statement ')' statement				{ $$ = new ForLoop($3, new ConditionEvaluation($4), $6); }
	| FOR '(' expression_statement expression_statement expression ')' statement	{ $$ = new ForLoop($3, new ConditionEvaluation($4), $5, $7); }
	| DO statement WHILE '(' expression ')' ';'										{ $$ = new DoWhileLoop($2, new ConditionEvaluation($5)); }
	;

%%

Node *g_root;

Node *ParseAST(std::string file_name)
{
  yyin = fopen(file_name.c_str(), "r");
  if(yyin == NULL){
    std::cerr << "Couldn't open input file: " << file_name << std::endl;
    exit(1);
  }
  g_root = nullptr;
  yyparse();
  fclose(yyin);
  yylex_destroy();
  return g_root;
}
