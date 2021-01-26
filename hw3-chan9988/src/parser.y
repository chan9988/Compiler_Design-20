%{
#include "visitor/AstNodeVisitor.hpp"
#include "AST/AstDumper.hpp"
#include "AST/ast.hpp"
#include "AST/program.hpp"
#include "AST/decl.hpp"
#include "AST/variable.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/function.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/print.hpp"
#include "AST/expression.hpp"
#include "AST/BinaryOperator.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/FunctionInvocation.hpp"
#include "AST/VariableReference.hpp"
#include "AST/assignment.hpp"
#include "AST/read.hpp"
#include "AST/if.hpp"
#include "AST/while.hpp"
#include "AST/for.hpp"
#include "AST/return.hpp"

#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>

#define YYLTYPE yyltype

typedef struct YYLTYPE {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

struct _id{
	char * name;
	int i,j;
};

struct _type{
	int scalartype;
	std::vector<int> *arr;
};

struct _constant{
	int intconstant; // type=0
	double doubleconstant;  // type=1
	char * str;  // type=2
	int type;
};

struct _argulist{
	AstNode *node;
	std::vector<int> *arr;
};

/* Declared by scanner.l */
extern uint32_t line_num;
extern char buffer[512];
extern FILE *yyin;
extern char *yytext;
/* End */

static AstNode *root;
static AstDumper vi;


extern "C" int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);
%}

%code requires {
    class AstNode;
}

    /* For yylval */
%union {
    /* basic semantic value */
    char *identifier;
    int intvalue;
	double doublevalue;
	std::vector<_id> *list;
	std::vector<_type> *typelist;
	std::vector<_argulist> *arglist;
	std::vector<AstNode *> *li;
    AstNode *node;
	_type ty;
	_constant con;
	_argulist arg;
};

%type <identifier> ProgramName FunctionName 
%type <list> IdList
%type <ty> Type ArrType ArrDecl
%type <intvalue> NegOrNot ScalarType ReturnType
%type <con> LiteralConstant IntegerAndReal StringAndBoolean
%type <li> DeclarationList Declarations FunctionList Functions StatementList Statements ExpressionList Expressions ArrRefList ArrRefs
%type <node> Declaration Function FunctionDeclaration FunctionDefinition CompoundStatement Simple Statement Expression FunctionInvocation FunctionCall VariableReference ElseOrNot Condition While For Return
%type <arg> FormalArg
%type <arglist> FormalArgs FormalArgList

    /* Delimiter */
%token COMMA SEMICOLON COLON
%token L_PARENTHESIS R_PARENTHESIS
%token L_BRACKET R_BRACKET

    /* Operator */
%token <identifier> ASSIGN
%left <identifier> OR
%left <identifier> AND
%right <identifier> NOT
%left <identifier> LESS LESS_OR_EQUAL EQUAL GREATER GREATER_OR_EQUAL NOT_EQUAL
%left <identifier> PLUS MINUS
%left <identifier> MULTIPLY DIVIDE MOD
%right <identifier> UNARY_MINUS

    /* Keyword */
%token ARRAY
%token <identifier>  BOOLEAN INTEGER REAL STRING
%token END BEGIN_ /* Use BEGIN_ since BEGIN is a keyword in lex */
%token DO ELSE FOR IF THEN WHILE
%token DEF OF TO RETURN VAR
%token <identifier> FALSE TRUE
%token <node> PRINT READ

    /* Identifier */
%token <identifier> ID

    /* Literal */
%token <intvalue> INT_LITERAL
%token <doublevalue> REAL_LITERAL
%token <identifier> STRING_LITERAL

%%
    /*
       Program Units
                     */

Program:
    ProgramName SEMICOLON
    /* ProgramBody */
    DeclarationList FunctionList CompoundStatement
    /* End of ProgramBody */
    END {
        root = new ProgramNode(@1.first_line, @1.first_column,
                               $1);       
		//free($1);
		if($3!=NULL){
			for(auto i: *($3)){
				root->add_child(i);
			}
		}
		if($4!=NULL){
			for(auto i: *($4)){
				root->add_child(i);
			}
		}
		root->add_child($5);
    }
;

ProgramName:
    ID
;

DeclarationList:
    Epsilon	{
		$$=NULL;
	}
    |
    Declarations {
		$$=new std::vector<AstNode *>;
		for(auto i : *($1)){
			$$->push_back(i);
		}
	}
;

Declarations:
    Declaration {
		$$=new std::vector<AstNode *>;
		$$->push_back($1);
	}
    |
    Declarations Declaration {
		$$=new std::vector<AstNode *>;
		for(auto i : *($1)){
			$$->push_back(i);
		}
		$$->push_back($2);
	}
;

FunctionList:
    Epsilon {
		$$=NULL;
	}
    |
    Functions {
		$$=new std::vector<AstNode *>;
		for(auto i : *($1)){
			$$->push_back(i);
		}
	}
;

Functions:
    Function {
		$$=new std::vector<AstNode *>;
		$$->push_back($1);
	}
    |
    Functions Function {
		$$=new std::vector<AstNode *>;
		for(auto i : *($1)){
			$$->push_back(i);
		}
		$$->push_back($2);
	}
;

Function:
    FunctionDeclaration
    |
    FunctionDefinition
;

FunctionDeclaration:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON {
		$$= new FunctionNode(@1.first_line,@1.first_column,$1,$5);
				
		if($3!=NULL){		
			for(auto i:*($3)){
				$$->add_de(i.node);
				//i.node->print();
				for(auto j: *(i.arr)){
					$$->add_arg(j);
					//printf("%d\n",j);
				}
			}
			//printf("\n");
		}
		//$$->print();
	}
;

FunctionDefinition:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType
    CompoundStatement
    END		{
		$$= new FunctionNode(@1.first_line,@1.first_column,$1,$5);
				
		if($3!=NULL){		
			for(auto i:*($3)){
				$$->add_de(i.node);
				//i.node->print();
				for(auto j: *(i.arr)){
					$$->add_arg(j);
					//printf("%d\n",j);
				}
			}
			//printf("\n");
		}
		$$->add_compoundstatement($6);
		//$$->print();
	}
;

FunctionName:
    ID
;

FormalArgList:
    Epsilon {
		$$=NULL;
	}
    |
    FormalArgs 	{
		$$=new std::vector<_argulist>;
		for(auto i : *($1)){
			$$->push_back(i);
		}
	}
;

FormalArgs:
    FormalArg {
		$$=new std::vector<_argulist>;
		$$->push_back($1);
	}
    |
    FormalArgs SEMICOLON FormalArg {
		$$=new std::vector<_argulist>;
		for(auto i : *($1)){
			$$->push_back(i);
		}
		$$->push_back($3);
	}
;

FormalArg:
    IdList COLON Type {
		AstNode *ne,*ne1;
		ne = new DeclNode(@1.first_line,@1.first_column);
		$$.arr= new std::vector<int>;
		for(auto i: *($1)){
			ne1= new VariableNode(i.i, i.j, i.name,$3.scalartype,$3.arr,0,0,NULL);		
			ne->add_child(ne1);	
			$$.arr->push_back($3.scalartype);
			$$.arr->push_back(-1);
			for(auto j: *($3.arr)){
				$$.arr->push_back(j);				
				//printf("%d ",j);
				//printf("\n");
			}
			$$.arr->push_back(-1);						
		}		
		//printf("\n");
		//printf("%d ",$3.scalartype);
		//for(auto i: *($3.arr)){
		//	printf(" %d",i);
		//}
		//printf("\n");
		//ne->print();		
		$$.node=ne;
		//$$.node->print();
		//for(auto i: *($$.arr)){
		//	printf("%d\n",i);
		//}
	}
;

IdList:
    ID	{
			$$=new std::vector<_id>;
			_id a;
			a.name=$1; a.i=@1.first_line; a.j=@1.first_column;
			$$->push_back(a);			
	}
    |
    IdList COMMA ID {
		$$=new std::vector<_id>;
		for(auto i : *($1)){
			$$->push_back(i);
		}
		_id a;
		a.name=$3; a.i=@3.first_line; a.j=@3.first_column;
		$$->push_back(a);
		//free($1);
	}
;

ReturnType:
    COLON ScalarType {
		$$=$2;
	}
    |
    Epsilon {
		$$=4;
	}	
;

    /*
       Data Types and Declarations
                                   */

Declaration:
    VAR IdList COLON Type SEMICOLON {			
			$$ = new DeclNode(@1.first_line,@1.first_column);		
			AstNode *ne;
			
			for(auto i: *($2)){
				ne= new VariableNode(i.i, i.j, i.name,$4.scalartype,$4.arr,0,0,NULL);		
				$$->add_child(ne);		
				//std::cout << i.name << " " << i.i << " " << i.j << std::endl;			
			}
			//std::cout << $4.scalartype ;
			//for(auto i: *($4.arr)){
			//	std::cout  << " " << i;			
			//}
			//std::cout << std::endl;
			
	}
	
    |
    VAR IdList COLON LiteralConstant SEMICOLON {
			$$ = new DeclNode(@1.first_line,@1.first_column);			
			AstNode *ne;
			AstNode *ne1;			
			for(auto i: *($2)){
				if($4.type==0){
					ne= new VariableNode(i.i, i.j, i.name,$4.type,NULL,$4.intconstant,0,NULL);
					ne1= new ConstantValueNode(@4.first_line,@4.first_column,$4.type,$4.intconstant,0,NULL);
					ne->add_child(ne1);
					$$->add_child(ne);
				}
				else if($4.type==1){
					ne= new VariableNode(i.i, i.j, i.name,$4.type,NULL,0,$4.doubleconstant,NULL);
					ne1= new ConstantValueNode(@4.first_line,@4.first_column,$4.type,0,$4.doubleconstant,NULL);
					ne->add_child(ne1);
					$$->add_child(ne);
				}
				else if($4.type==2){
					if(strcmp($4.str,"true")==0||strcmp($4.str,"false")==0){
						ne= new VariableNode(i.i, i.j, i.name,3,NULL,0,0,$4.str);
						ne1= new ConstantValueNode(@4.first_line,@4.first_column,2,0,0,$4.str);
						ne->add_child(ne1);
					}
					else{
						ne= new VariableNode(i.i, i.j, i.name,2,NULL,0,0,$4.str);
						ne1= new ConstantValueNode(@4.first_line,@4.first_column,3,0,0,$4.str);
						ne->add_child(ne1);
					}
					$$->add_child(ne);
				}	
			}
			//if($4.type==0){
				//printf("%d %d %d\n",$4.intconstant,@4.first_line,@4.first_column);
				//std::cout << $4.intconstant << " " << @4.first_line << " " << @4.first_column << std::endl;
			//}
			//if($4.type==1){
				//printf("%f %d %d\n",$4.doubleconstant,@4.first_line,@4.first_column);
			//}
			//if($4.type==2){
				//std::cout << $4.str << " " << @4.first_line << " " << @4.first_column << std::endl;
			//}
			//std::cout << std::endl;
	}
;

Type:
    ScalarType {
		$$.scalartype=$1;
		$$.arr=new std::vector<int>;	
	}
    |
    ArrType {
		$$=$1;
	}
;

ScalarType:
    INTEGER { $$=0;}
    |
    REAL { $$=1;}
    |
    STRING  { $$=2;}
    |
    BOOLEAN  { $$=3;}
;

ArrType:
    ArrDecl ScalarType {
		$$=$1;
		$$.scalartype=$2;
	}
;

ArrDecl:
    ARRAY INT_LITERAL OF {
		$$.arr=new std::vector<int>;
		$$.arr->push_back($2);
	} 
    |
    ArrDecl ARRAY INT_LITERAL OF {
		$$=$1;
		$$.arr->push_back($3);
	}
;

LiteralConstant:
    NegOrNot INT_LITERAL {
		$$.intconstant=$1*$2;
		@$.first_line=@2.first_line;
		@$.first_column=@2.first_column;
		$$.type=0;
	}
    |
    NegOrNot REAL_LITERAL {
		$$.doubleconstant=$1*$2;
		$$.type=1;
	}
    |
    StringAndBoolean {
		$$.str=$1.str;
		$$.type=2;
	}
;

NegOrNot:
    Epsilon {
		$$=1;
	}
    |
    MINUS %prec UNARY_MINUS{
		$$=-1;
	}
;

StringAndBoolean:
    STRING_LITERAL {
		$$.type=2;
		$$.str=$1;
	}
    |
    TRUE {
		$$.type=3;
		$$.str=$1;

	}
    |
    FALSE {
		$$.type=3;
		$$.str=$1;

	}
;

IntegerAndReal:
    INT_LITERAL {
		$$.type=0;
		$$.intconstant=$1;
    	}
    |
    REAL_LITERAL {
		$$.type=1;
		$$.doubleconstant=$1;
	}
;

    /*
       Statements
                  */

Statement:
    CompoundStatement
    |
    Simple 
    |
    Condition 
    |
    While 
    |
    For 
    |
    Return 
    |
    FunctionCall 
;

CompoundStatement:
    BEGIN_
    DeclarationList
    StatementList
    END {
		$$ = new CompoundStatementNode(@1.first_line,@1.first_column);
		if($2!=NULL){
			for(auto i: *($2)){
				$$->add_de(i);
			}
		}
		if($3!=NULL){
			for(auto i: *($3)){
				$$->add_st(i);
			}
		}  
	}
;

Simple:
    VariableReference ASSIGN Expression SEMICOLON {
		$$ = new AssignmentNode(@2.first_line,@2.first_column,$1,$3);
		//$$ -> print();
		//printf("\n");
	}
    |
    PRINT Expression SEMICOLON {
		if($2!=NULL){
			//$2->print();
			$$ = new PrintNode(@1.first_line,@1.first_column,$2);
			//$$->print();
		}
	}
    |
    READ VariableReference SEMICOLON {
		if($2!=NULL){
			$$= new ReadNode(@1.first_line,@1.first_column,$2);
		}
	}
;

VariableReference:
    ID ArrRefList {
		$$= new VariableReferenceNode(@1.first_line,@1.first_column,$1);
		if($2!=NULL){
			for(auto i : *($2)){
				//i->print();
				$$->add_child(i);
			}
		}
		
		//$$->print();
	}
;

ArrRefList:
    Epsilon {
		$$=NULL;
	}	
    |
    ArrRefs {
		$$=new std::vector<AstNode *>;
		for(auto i : *($1)){
			$$->push_back(i);
			//i->print();
		}
	}
;

ArrRefs:
    L_BRACKET Expression R_BRACKET {
		//if($2!=NULL) $2->print();
		$$=new std::vector<AstNode *>;
		if($2!=NULL){
			$$->push_back($2);
			//$2->print();
		}	
	}	
    |
    ArrRefs L_BRACKET Expression R_BRACKET {
		//if($3!=NULL) $3->print();
		$$=new std::vector<AstNode *>;
		for(auto i : *($1)){
			$$->push_back(i);
		}
		if($3!=NULL)
			$$->push_back($3);
			//$3->print();
	}	
;

Condition:
    IF Expression THEN
    CompoundStatement
    ElseOrNot
    END IF {
		$$ = new IfNode(@1.first_line,@1.first_column,$2,$4,$5);
		//$$->print();
	}
;

ElseOrNot:
    ELSE
    CompoundStatement { $$=$2;}
    |
    Epsilon {$$=NULL;}
;

While:
    WHILE Expression DO
    CompoundStatement
    END DO {
		$$ = new WhileNode(@1.first_line,@1.first_column,$2,$4);
	}
;

For:
    FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO
    CompoundStatement 
    END DO {
		AstNode *ne,*ne1;
		ne= new DeclNode(@2.first_line,@2.first_column); // decl
		ne1= new VariableNode(@2.first_line,@2.first_column,$2,NULL,0,0,0,NULL);  // var
		ne->add_child(ne1);
		//ne->print();
		AstNode *ne2,*ne3,*ne4;
		ne2= new VariableReferenceNode(@2.first_line,@2.first_column,$2);  // varref
		ne3 = new  ConstantValueNode(@4.first_line,@4.first_column,0,$4,0,NULL);  // const
		ne4 = new AssignmentNode(@3.first_line,@3.first_column,ne2,ne3); // assign
		//ne4->print();
		AstNode *ne5;
		ne5 = new ConstantValueNode(@6.first_line,@6.first_column,0,$6,0,NULL);  // const
		//ne5->print();
		//$8->print();
		$$ = new ForNode(@1.first_line,@1.first_column,ne,ne4,ne5,$8);
		//$$->print();
	}
;

Return:
    RETURN Expression SEMICOLON {
		$$ = new ReturnNode(@1.first_line,@1.first_column,$2);
	}
;

FunctionCall:
    FunctionInvocation SEMICOLON 
;

FunctionInvocation:
    ID L_PARENTHESIS ExpressionList R_PARENTHESIS {
		$$=new FunctionInvocationNode(@1.first_line,@1.first_column,$1);
		if($3!=NULL){
			for(auto i: *($3)){
				//i->print();
				$$->add_child(i);
			}
		}
		//$$->print();
	}
;

ExpressionList:
    Epsilon {
		$$=NULL;
	}	
    |
    Expressions {
		$$=new std::vector<AstNode *>;
		for(auto i : *($1)){
			$$->push_back(i);
		}
	}
;

Expressions:
    Expression {
		$$=new std::vector<AstNode *>;
		$$->push_back($1);
	}
    |
    Expressions COMMA Expression {
		$$=new std::vector<AstNode *>;
		for(auto i : *($1)){
			$$->push_back(i);
		}
		if($3!=NULL)
			$$->push_back($3);
	}
;

StatementList:
    Epsilon	{
		$$=NULL;
	}	
    |
    Statements {
		$$=new std::vector<AstNode *>;
		for(auto i : *($1)){
			$$->push_back(i);
		}
	}
;

Statements:
    Statement {
		$$=new std::vector<AstNode *>;
		$$->push_back($1);
	}
    |
    Statements Statement {
		$$=new std::vector<AstNode *>;
		for(auto i : *($1)){
			$$->push_back(i);
		}
		if($2!=NULL)
			$$->push_back($2);
	}
;

Expression:
    L_PARENTHESIS Expression R_PARENTHESIS {$$=$2;}
    |
    MINUS Expression %prec UNARY_MINUS {
		if($1!=NULL){		
			$$ = new UnaryOperatorNode(@1.first_line,@1.first_column,"neg",$2);
			//$$->print();
		}		
	}
    |
    Expression MULTIPLY Expression {
		if($1!=NULL&&$3!=NULL){		
			$$ = new BinaryOperatorNode(@2.first_line,@2.first_column,$2,$1,$3);
			//$$->print();
		}		
	}
    |
    Expression DIVIDE Expression {
		if($1!=NULL&&$3!=NULL){		
			$$ = new BinaryOperatorNode(@2.first_line,@2.first_column,$2,$1,$3);
			//$$->print();
		}		
	}
    |
    Expression MOD Expression {
		if($1!=NULL&&$3!=NULL){		
			$$ = new BinaryOperatorNode(@2.first_line,@2.first_column,$2,$1,$3);
			//$$->print();
		}		
	}
    |
    Expression PLUS Expression {
		if($1!=NULL&&$3!=NULL){		
			$$ = new BinaryOperatorNode(@2.first_line,@2.first_column,$2,$1,$3);
			//$$->print();
		}		
	}
    |
    Expression MINUS Expression {
		if($1!=NULL&&$3!=NULL){		
			$$ = new BinaryOperatorNode(@2.first_line,@2.first_column,$2,$1,$3);
			//$$->print();
		}		
	}
    |
    Expression LESS Expression {
		if($1!=NULL&&$3!=NULL){		
			$$ = new BinaryOperatorNode(@2.first_line,@2.first_column,$2,$1,$3);
			//$$->print();
		}		
	}
    |
    Expression LESS_OR_EQUAL Expression {
		if($1!=NULL&&$3!=NULL){		
			$$ = new BinaryOperatorNode(@2.first_line,@2.first_column,$2,$1,$3);
			//$$->print();
		}		
	}
    |
    Expression GREATER Expression {
		if($1!=NULL&&$3!=NULL){		
			$$ = new BinaryOperatorNode(@2.first_line,@2.first_column,$2,$1,$3);
			//$$->print();
		}		
	}
    |
    Expression GREATER_OR_EQUAL Expression {
		if($1!=NULL&&$3!=NULL){		
			$$ = new BinaryOperatorNode(@2.first_line,@2.first_column,$2,$1,$3);
			//$$->print();
		}		
	}
    |
    Expression EQUAL Expression {
		if($1!=NULL&&$3!=NULL){		
			$$ = new BinaryOperatorNode(@2.first_line,@2.first_column,$2,$1,$3);
			//$$->print();
		}		
	}
    |
    Expression NOT_EQUAL Expression {
		if($1!=NULL&&$3!=NULL){		
			$$ = new BinaryOperatorNode(@2.first_line,@2.first_column,$2,$1,$3);
			//$$->print();
		}		
	}
    |
    NOT Expression   {
		if($1!=NULL){		
			$$ = new UnaryOperatorNode(@1.first_line,@1.first_column,"not",$2);
			//$$->print();
		}		
	}
    |
    Expression AND Expression {
		if($1!=NULL&&$3!=NULL){		
			$$ = new BinaryOperatorNode(@2.first_line,@2.first_column,$2,$1,$3);
			//$$->print();
		}		
	}
    |
    Expression OR Expression {
		if($1!=NULL&&$3!=NULL){		
			$$ = new BinaryOperatorNode(@2.first_line,@2.first_column,$2,$1,$3);
			//$$->print();
		}		
	}
    |
    IntegerAndReal { 
	if($1.type==0){
		$$ = new ConstantValueNode(@1.first_line,@1.first_column,$1.type,$1.intconstant,0,NULL);
	}
	else if($1.type==1){
		$$ = new ConstantValueNode(@1.first_line,@1.first_column,$1.type,0,$1.doubleconstant,NULL);
	}	
		//$$->print(); 
	}
    |
    StringAndBoolean { 
	$$ = new ConstantValueNode(@1.first_line,@1.first_column,$1.type,0,0,$1.str);	
	//$$->print();	
	}
    |
    VariableReference  {$$=$1; 
	//$1->print();
	}
    |
    FunctionInvocation {$$=$1;}
;

    /*
       misc
            */
Epsilon:
;
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
    if (argc < 2) {
        fprintf(stderr, "Usage: ./parser <filename> [--dump-ast]\n");
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    assert(yyin != NULL && "fopen() fails.");

    yyparse();
	

    if (argc >= 3 && strcmp(argv[2], "--dump-ast") == 0) {
        //root->print();
	root->accept(vi);
    }

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");

    delete root;
    fclose(yyin);
    yylex_destroy();
    return 0;
}
