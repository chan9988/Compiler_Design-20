%{
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern int32_t line_num;   /* declared in scanner.l */
extern char buffer[512];  /* declared in scanner.l */
extern FILE *yyin;        /* declared by lex */
extern char *yytext;      /* declared by lex */

extern int yylex(void); 
static void yyerror(const char *msg);
%}

%token ARRAY Begin BOOLEAN DEF DO ELSE END FALSE FOR INTEGER IF OF PRINT READ REAL STRING THEN TO TRUE RETURN VAR WHILE ID DINT OINT FLOAT SCIENT STR MOD ASSIGN LT LE LG GE GT EQ AND OR NOT 
%start program_name
%left '-'
%left '*'
%left '/'
%left MOD
%left '+'
%left LT 
%left LE 
%left LG 
%left GE 
%left GT 
%left EQ
%left AND 
%left OR 
%left NOT

%%

program_name: ID ';' v_and_c_declaration fun compound_statement END ;
v_and_c_declaration: /* empty */ | v_and_c_declaration1 ;
v_and_c_declaration1: v_and_c_declaration1  variable  
	   | v_and_c_declaration1  constant 
	   | variable 
	   | constant  ;
fun: /* empty */ | fun1 ;
fun1: fun1  function_declaration 
    | fun1  function_definition 
    | function_declaration 
    | function_definition  ;

// Function

function_declaration: ID '(' arguments ')' ':' scaler_type ';' 
		    | ID '(' arguments ')' ';' ;
function_definition: ID '(' arguments ')' ':' scaler_type  compound_statement END 
		   | ID '(' arguments ')' compound_statement END ;
arguments: /* empty */ | arguments1 ;
arguments1: arguments1 ';' arg | arg ; 
arg: id_list ':' type ;
id_list: id_list ',' ID | ID ;

// Variable

variable: VAR id_list ':' scaler_type ';' 
	| VAR id_list ':' ARRAY int_constant  OF type ';' ;
scaler_type: INTEGER | REAL | STRING | BOOLEAN ;
type: INTEGER | REAL | STRING | BOOLEAN | ARRAY int_constant OF type ;
int_constant: DINT | OINT  ;

// Constant

constant: VAR id_list ':' literal_constant ';' ;
literal_constant: STR | TRUE | FALSE | neg number  ;
number: DINT | OINT | FLOAT | SCIENT ;
// neg_number: neg DINT | neg OINT | neg FLOAT | neg SCIENT ;
neg: '-' | /*empty*/ ;

// compound statements

compound_statement: Begin v_and_c_declaration statements  END ;
statements: /* empty */ | statements1 ;
statements1: statements1  statement_union  | statement_union ;
statement_union: simple_statement 
	       | conditional_statement
	       | while_statement
	       | for_statement
	       | return_statement
	       | procedure_call_statement  
	       | compound_statement ;

// simple statement

simple_statement: variable_reference ASSIGN expression ';'
	       | PRINT variable_reference ';'
	       | PRINT expression ';'
	       | READ variable_reference ';' ;
variable_reference: ID | ID array_reference ;
array_reference: array_reference '[' expression ']' 
	       | '[' expression ']' ;

// conditional statement

conditional_statement: IF expression THEN compound_statement ELSE compound_statement END IF
	   	     | IF expression THEN compound_statement END IF ;

// while statement

while_statement: WHILE expression DO compound_statement END DO ;

// for statement

for_statement: FOR ID ASSIGN int_constant TO int_constant DO compound_statement END DO ;

// return statement

return_statement: RETURN expression ';' ;

// procedure call statement

procedure_call_statement: ID '(' more_expression ')' ';' ;
more_expression: /* empty */ | more_expression1 ;
more_expression1: expression | more_expression1 ',' expression ;

// expressions

expression: e;
e: '-' e|  e '-' e | e '*' e | e '/' e | e MOD e | e '+' e  
 | e LT e | e LE e | e LG e | e GE e | e GT e | e EQ e 
 | e AND e | e OR e | NOT e | NOT  
 | '(' e ')' | literal_constant | variable_reference   
 | function_invocations ;
function_invocations: ID '(' exp ')' ;
exp: /* empty */ | exp1 ;
exp1: exp1 ',' expression | expression ;


%%

void yyerror(const char *msg) {
    fprintf(stderr,
            "\n"
            "|-----------------------------------------------------------------"
            "---------\n"
            "| Error found in Line #%d: %s\n"
            "|\n"
            "| Unmatched token: %s\n"
            "|-----------------------------------------------------------------"
            "---------\n",
            line_num, buffer, yytext);
    exit(-1);
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./parser <filename>\n");
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    assert(yyin != NULL && "fopen() fails.");

    yyparse();

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");
    return 0;
}
