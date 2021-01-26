%{
#include <stdint.h>

#define LIST                strCat(yytext)
#define TOKEN(t)            { LIST; if (opt_tok) printf("<%s>\n", #t); }
#define TOKEN_CHAR(t)       { LIST; if (opt_tok) printf("<%c>\n", (t)); }
#define TOKEN_STRING(t, s)  { LIST; if (opt_tok) printf("<%s: %s>\n", #t, (s)); }
#define MAX_LINE_LENG       512

uint32_t line_num = 1;
char buffer[MAX_LINE_LENG];

static int32_t opt_src = 1;
static int32_t opt_tok = 1;
static char *buffer_ptr = buffer;

static void strCat(const char *Text);

%}

%x CC
dec  [1-9][0-9]*|[0]
flo  (0|[1-9][0-9]*)\.(0|[0-9]*[1-9])
oct  [0][0-7]*

%%

"(" { TOKEN_CHAR('('); }   // Delimiters
")" { TOKEN_CHAR(')'); }
"," { TOKEN_CHAR(','); }
";" { TOKEN_CHAR(';'); }
":" { TOKEN_CHAR(':'); }
"]" { TOKEN_CHAR(']'); }
"[" { TOKEN_CHAR('['); }

"+" { TOKEN_CHAR('+'); }   //  Arithmetic Operators
"-" { TOKEN_CHAR('-'); }
"*" { TOKEN_CHAR('*'); }
"/" { TOKEN_CHAR('/'); }
"mod" { TOKEN(mod); }
":=" { TOKEN(:=); }
"<" { TOKEN_CHAR('<'); }    //  Relational Operators
"<=" { TOKEN(<=); }
"<>" { TOKEN(<>); }
">=" { TOKEN(>=); }
">" { TOKEN_CHAR('>'); }
"=" { TOKEN_CHAR('='); }
"and" { TOKEN(and); }        //  Logical Operators
"or" { TOKEN(or); }
"not" { TOKEN(not); }

"array" TOKEN(KWarray);      //   Keywords
"begin" TOKEN(KWbegin);
"boolean" TOKEN(KWboolean);
"def" TOKEN(KWdef);
"do" TOKEN(KWdo);
"else" TOKEN(KWelse);
"end" TOKEN(KWend);
"false" TOKEN(KWfalse);
"for" TOKEN(KWfor);
"integer" TOKEN(KWinteger);
"if" TOKEN(KWif);
"of" TOKEN(KWof);
"print" TOKEN(KWprint);
"read" TOKEN(KWread);
"real" TOKEN(KWreal);
"string" TOKEN(KWstring);
"then" TOKEN(KWthen);
"to" TOKEN(KWto);
"true" TOKEN(KWtrue);
"return" TOKEN(KWreturn);
"var" TOKEN(KWvar);
"while" TOKEN(KWwhile);

[a-zA-Z][0-9a-zA-Z]* TOKEN_STRING(id,yytext);   // Identifiers

{dec} TOKEN_STRING(integer,yytext);      //  Interger decimal 
{oct} TOKEN_STRING(oct_integer,yytext);    //  Interger Octal

{flo}   TOKEN_STRING(float,yytext);  // float

({dec}|{flo})(E|e)(\+|\-)??{dec}  TOKEN_STRING(scientific,yytext);      // Scientific Notations 

\"([^\"\n]|\"\")*\"   {
	int i=0,j=0;
	char s[MAX_LINE_LENG];
	while(yytext[i]!='\0'){
		if(i==0){
			i++;		
		}		
		else if(yytext[i]=='\"'&&yytext[i+1]!='\"'){
			i++;			
		}
		else if(yytext[i]=='\"'&&yytext[i+1]=='\"'&&i!=0){
			s[j]=yytext[i];
			i+=2;
			j++;
		}
		else{
			s[j]=yytext[i];				
			i++;
			j++;		
		}
	}
	s[j]='\0';
	TOKEN_STRING(string,s); 
}// string

[ ]|\t   LIST;       // Whitespace & tab

"//&S+".*  {LIST;opt_src=1;}  // Pseudocomments
"//&S-".*  {LIST;opt_src=0;}
"//&T+".*  {LIST;opt_tok=1;}
"//&T-".*  {LIST;opt_tok=0;}
"//".*  LIST;

<CC>.      LIST;		// comment state
<CC>"*/"   {LIST;BEGIN 0;}
<CC>\n     {
    if (opt_src) {
        printf("%d: %s\n", line_num, buffer);
    }
    ++line_num;
    buffer[0] = '\0';
    buffer_ptr = buffer;
}
"/*"	  {LIST;BEGIN CC;}


\n {
    if (opt_src) {
        printf("%d: %s\n", line_num, buffer);
    }
    ++line_num;
    buffer[0] = '\0';
    buffer_ptr = buffer;
}



    /* Catch the character which is not accepted by rules above */
. {
    printf("Error at line %d: bad character \"%s\"\n", line_num, yytext);
    exit(-1);
}

%%

static void strCat(const char *Text) {
    while (*Text) {
        *buffer_ptr++ = *Text++;
    }
    *buffer_ptr = '\0';
}

int main(int argc, const char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./scanner [filename]\n");
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        fprintf(stderr, "Open file error\n");
        exit(-1);
    }

    yylex();

    return 0;
}
