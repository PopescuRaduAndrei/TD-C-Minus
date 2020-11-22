%{ 
  #include <stdio.h>
  #include "ast.h"

  Node* astRoot = NULL;
  int yyerror(char * c);
  extern int yylex(void);
%}

%union{
	Node *node;
	char* strings;
	int intVal;
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
%token NUM 
%token ID

%type <node> program declaration_list declaration 
%type <node> var_declaration fun_declaration type_specifier 
%type <node> local_declarations statement_list statement
%type <node> expression_stmt selection_stmt iteration_stmt return_stmt 
%type <node> expression var
%type <node> simple_expression additive_expression term factor call args arg_list
%type <value> relop addop mulop

%start program

%%

program : declaration_list {astRoot = $1;}
                                                                  
declaration_list : declaration_list declaration             {$$ = newDecList($1, $2);}
                 | declaration                              {$$ = $1;}
                 ;

declaration  : var_declaration                              {$$ = $1;}
	         | fun_declaration                              {$$ = $1;}
             ;

var_declaration : type_specifier ID                         {$$ = newVarDec($1, $2);}
                | type_specifier ID LBRACKET NUM RBRACKET   {$$ = newArrayDec($1, $2, $4);}
                ;

type_specifier : INT {$$ = newTypeSpe(TYPE_INTEGER);}
               | VOID {$$ = newTypeSpe(TYPE_VOID);}
	           ;

fun_declaration : type_specifier ID LPAREN params RPAREN compound_stmt {$$ = newFunDec($1, $2, $4, $6);}	              
                ;

params : param_list                                         {$$ = $1;}
		| VOID ;                                            {$$ = NULL;}

param_list : param_list COMMA param                         {$$ = newParamList($1, $3);}
           | param                                          {$$ = newParamList(NULL, $1);}		            
	        ;

param : type_specifier ID                                   {$$ = newParam($1, $2, 0);}                                         
      | type_specifier ID LBRACKET RBRACKET                 {$$ = newParam($1, $2, 1);}
      ;

compound_stmt : LBRACE local_declarations statement_list RBRACE {$$ = newCompound($2, $3);}
              ;

local_declarations : local_declarations var_declaration {$$ = newLocalDecs($1, $2);}
                   |                                    {$$ = NULL;}
                   ;

statement_list : statement_list statement               {$$ = newStmtList($1, $2);}
               |                                        {$$ = NULL;}
               ;

statement : expression_stmt                             {$$ = $1;}
          | compound_stmt                               {$$ = $1;}
          | selection_stmt                              {$$ = $1;}
          | iteration_stmt                              {$$ = $1;}
          | return_stmt                                 {$$ = $1;}
		  ;

expression_stmt : expression END_OF_INSTRUCTION         {$$ = $1;}
                | END_OF_INSTRUCTION                    {$$ = NULL;}
				;

selection_stmt : IF  LPAREN expression RPAREN  statement                    {$$ = newSelectStmt($3,$5,NULL);}
               | IF  LPAREN expression RPAREN  statement ELSE statement	    {$$ = newSelectStmt($3,$5,$7);}				 	          
               ;

iteration_stmt : WHILE LPAREN expression RPAREN statement                   {$$ = newIterStmt($3, $5);}    
                 ;
				

return_stmt : RETURN END_OF_INSTRUCTION                                     {$$ = newRetStmt(NULL);}
            | RETURN expression END_OF_INSTRUCTION                          {$$ = newRetStmt($2);}
            ;

expression : var ASSIGN expression                                          {$$ = newAssignExp($1, $3);}
           | simple_expression                                              {$$ = $1;}
           ;

var : ID                                                                    {$$ = newVar($1);}
    | ID LBRACKET expression RBRACKET                                       {$$ = newArrayVar($1, $3);}
    ;

simple_expression : additive_expression relop additive_expression           {$$ = newSimpExp($1, $2, $3);}
                  | additive_expression                                     {$$ = $1;}
                  ;

relop : LOWEROREQUAL                                                        {$$ = LOWEROREQUAL;}
	  | LOWER                                                               {$$ = LOWER;}
	  | GREATEROREQUAL                                                      {$$ = GREATEROREQUAL;}
	  | GREATER                                                             {$$ = GREATER;}
	  | EQUAL                                                               {$$ = EQUAL;}
	  | NOTEQUAL                                                            {$$ = NOTEQUAL;}
	  ;

additive_expression : additive_expression addop term                        {$$ = newAddExp($1, $2, $3);}
                    | term                                                  {$$ = $1;}
                    ;

addop : ADD                                                                 {$$ = ADD;}
      | SUBSTRACT                                                           {$$ = SUBSTRACT;}
      ;

term : term mulop factor                                                    {$$ = newTerm($1, $2, $3);}
     | factor                                                               {$$ = $1;}
     ;

mulop : MULTIPLY                                                            {$$ = MULTIPLY;}
      | DIVIDE                                                              {$$ = DIVIDE;}
      ;

factor : LPAREN expression RPAREN                                           {$$ = $2;}
       | var                                                                {$$ = $1;}
       | call                                                               {$$ = $1;}
       | NUM                                                                {$$ = newNumNode($1);}
       ;

call : ID LPAREN args RPAREN                                                {$$ = newCall($1, $3);}
     ;

args : arg_list                                                             {$$ = $1;}
	 |                                                                      {$$ = NULL;}
	 ;

arg_list : arg_list END_OF_INSTRUCTION expression                           {$$ = newArgList($1, $3);}
         | expression                                                       {$$ = $1;}
         ;

%%

int yyerror(char *c){
    printf("Error");
}