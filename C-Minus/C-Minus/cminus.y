%{ 
  #include <stdio.h>
  #include "ast.h"

  Node* astRoot = NULL;
  int yyerror(char * c);
  extern int yylex(void);
%}

%union{
	Node* node;
	char* strings;
	int value;
}

%token END 
%token INT
%token LONG 
%token DOUBLE 
%token SHORT 
%token UNSIGNED 
%token VOID 
%token VOLATILE 
%token WHILE 
%token FLOAT 
%token IF 
%token ELSE
%token RETURN 
%token CONSTANT 
%token STRING_LITERAL 
%token ASSIGN 
%token ADD 
%token SUBSTRACT 
%token IDENTIFIER 
%token END_OF_INSTRUCTION 
%token EQUAL 
%token NOTEQUAL 
%token LOWER 
%token LOWEROREQUAL 
%token GREATER 
%token GREATEROREQUAL 
%token MULTIPLY 
%token DIVIDE 
%token LPAREN 
%token RPAREN 
%token LBRACKET 
%token RBRACKET 
%token LBRACE 
%token RBRACE 
%token COMMA 

%token <strings> ID
%token <value> NUM


%type <node> relop
%type <node> addop
%type <node> mulop
%type <node> program 
%type <node> declaration_list
%type <node> declaration
%type <node> var_declaration
%type <node> type_specifier
%type <node> fun_declaration 
%type <node> params
%type <node> params_list
%type <node> param
%type <node> compound_stmt
%type <node> local_declarations
%type <node> statement_list
%type <node> statement
%type <node> expression_stmt
%type <node> selection_stmt
%type <node> iteration_stmt
%type <node> return_stmt
%type <node> expression
%type <node> var
%type <node> simple_expression
%type <node> additive_expression
%type <node> term
%type <node> factor
%type <node> call
%type <node> args 
%type <node> arg_list

%start program

%%

program: declaration_list								{astRoot = createProgramUnitNode($1); $$ = astRoot;}
	   ;
	   
declaration_list: declaration declaration_list			{addLinkToList($$, $1); $$ = $2;}
                | declaration							{addLinkToList($$, $1);}
				;
				
selection_stmt : IF LPAREN expression RPAREN statement							{ $$ = createIfStatement($3, $5, NULL);}
			   | IF LPAREN expression RPAREN statement ELSE statement			{ $$ = createIfStatement($3, $5, $7);}
			   ;
			   
iteration_stmt : WHILE LPAREN expression RPAREN statement						{ $$ = createIterationStatementNode($3, $5); }
				;
				
declaration : var_declaration			{$$ = createDeclarationNode($1);}
            | fun_declaration			{$$ = createDeclarationNode($1);}
            ;
			
var_declaration : type_specifier ID END_OF_INSTRUCTION 									{$$ = createVarDeclaration($1, $2, 0);}
				| type_specifier ID LBRACKET NUM RBRACKET END_OF_INSTRUCTION			{$$ = createVarDeclaration($1, $2, $4);}
                ;

type_specifier : INT			{$$ = createTypeSpecifier("INT");}
				| VOID			{$$ = createTypeSpecifier("VOID");}
				;
				
fun_declaration : type_specifier ID LPAREN params RPAREN compound_stmt			{$$ = createFunctionDeclarationNode($1, $2, $4, $6);}
                ;
				
params : params_list			{$$ = createParametersDeclarationNode($1);}
	   | VOID					{$$ = createParametersDeclarationNode(NULL);}
	   ;
	   
params_list : params_list COMMA param			{$$ = $1;addLinkToList($$, $3);}
			| param								{$$ = createListNode("ParametersList", $1);}
			;
			
param : type_specifier ID									{ $$ = createVarDeclaration($1, $2, 0);}
	  | type_specifier ID LBRACKET RBRACKET					{ $$ = createVarDeclaration($1, $2, 0);}
	  ;
	  
compound_stmt : LBRACE local_declarations statement_list RBRACE		{$$ = createCompoundStatement($2, $3);}
			  ;

local_declarations
    : local_declarations var_declaration { $$ = $1; addLinkToList($$, $2); }
    |  { $$ = createListNode("LocalDeclarations", NULL); }
    ;
				   
statement_list
    : statement_list statement { $$ = $1; addLinkToList($$, $2); }
    |  { $$ = createListNode("StatementList", NULL); }
    ;

statement : expression_stmt					{$$ = createStatementNode($1);}
		  | compound_stmt					{$$ = createStatementNode($1);}
		  | selection_stmt					{$$ = createStatementNode($1);}
		  | iteration_stmt					{$$ = createStatementNode($1);}
		  | return_stmt						{$$ = createStatementNode($1);}
		  ;
		  
expression_stmt : expression END_OF_INSTRUCTION 			{$$ = createExpressionStatement($1);}
				| END_OF_INSTRUCTION 						{$$ = createExpressionStatement(NULL);}
				;
			   

return_stmt : RETURN END_OF_INSTRUCTION 					{$$ = createReturnStatement(NULL);}
			| RETURN expression END_OF_INSTRUCTION 			{$$ = createReturnStatement($2);}
			;
			
expression : var ASSIGN expression			{addLinkToList($$, $1);$$ = $3;}
		   | simple_expression				{$$ = createExpressionNode($1);}
		   ;
		   
var
    : ID { $$ = createVariableNode($1, NULL); }
    | ID LBRACKET expression RBRACKET { $$ = createVariableNode($1, $3); }
    ;
	
simple_expression : additive_expression relop additive_expression           {$$ = newSimpExp($1, $2, $3);}
                  | additive_expression                                     {$$ = $1;}
                  ;
				
relop
    : LOWEROREQUAL { $$ = createRelationalOperatorNode("<="); }
    | LOWER { $$ = createRelationalOperatorNode("<"); }
    | GREATER { $$ = createRelationalOperatorNode(">"); }
    | GREATEROREQUAL { $$ = createRelationalOperatorNode(">="); }
    | EQUAL { $$ = createRelationalOperatorNode("=="); }
    | NOTEQUAL { $$ = createRelationalOperatorNode("!="); }
    ;

additive_expression : additive_expression addop term                        {$$ = newAddExp($1, $2, $3);}
                    | term                                                  {$$ = $1;}
                    ;

addop
    : ADD { $$ = createAddSubOperatorNode("+"); }
    | SUBSTRACT { $$ = createAddSubOperatorNode("-"); }
    ;

term : term mulop factor                                                    {$$ = newTerm($1, $2, $3);}
     | factor                                                               {$$ = $1;}
     ;

mulop
    : MULTIPLY { $$ = createMulDivOperatorNode("*"); }
    | DIVIDE { $$ = createMulDivOperatorNode("/"); }
    ;


factor : LPAREN expression RPAREN                                           {$$ = $2;}
       | var                                                                {$$ = $1;}
       | call                                                               {$$ = $1;}
       | NUM                                                                {$$ = newNumNode(NULL, $1);}
       ;

call : ID LPAREN args RPAREN                                                {$$ = newCall($1, $3);}
     ;

args : arg_list                                                             {$$ = $1;}
	 |                                                                      {$$ = NULL;}
	 ;

arg_list
    : arg_list COMMA expression { $$ = $1; addLinkToList($$, $3); }
    | expression { $$ = createListNode("ArgumentsList", $1); }
    ;


%%

int yyerror(char * s) 
{    
	printf ( "%s\n", s); 
	return 0;
}  