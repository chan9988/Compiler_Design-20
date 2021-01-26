# hw2 report

|||
|-:|:-|
|Name|yourname|
|0716049|詹凱傑|

## How much time did you spend on this project

8 hours.

## Project overview

這次的作業是要我們寫一個context free grammar並用這個grammar產生parser來parse助教給的p語言

根據助教給的規則，可以產生下列的CFG。

Terminal有下列幾個，ARRAY Begin BOOLEAN DEF DO ELSE END FALSE FOR INTEGER IF OF PRINT READ REAL STRING THEN TO TRUE RETURN VAR WHILE ID DINT OINT FLOAT SCIENT STR MOD ASSIGN LT LE LG GE GT EQ AND OR NOT '-' '*' '/' '+' 。

Start state 是 program_name

1. program_name 會derive出整個program

   program_name -> ID ‘;’ v_and_c_declaration fun compound_statement END

2. v_and_c_declaration 表示會derive多個variable和constant(也可以0個)

   透過spec的提示，可以產生出下列的規則

   v_and_c_declaration - > ε | v_and_c_declaration1

   v_and_c_declaration1 ->  v_and_c_declaration1 variable | v_and_c_declaration1 constant | variable | constant

3. fun 表示會derive 出多個(也可以是0個)function的宣告和定義

   仿照第二項的規則寫出對應的fun和fun1

   fun  - > ε | fun1

   fun1  ->  fun1 function_declaration | fun1 function_definition | function_declaration | function_definition

4. 再來是variable 和 constant的定義

   variable可以宣告一個變數，並設定對應的型別，constant可以宣告一個變數給定這個變數一個值

   variable -> VAR id_list ':' scaler_type ';' | VAR id_list ':' ARRAY int_constant OF type ';'

   constant -> VAR id_list ':' literal_constant ';'

   以下是對於上面兩個規則中會用到的nonternimal 的定義  
   scaler_type -> INTEGER | REAL | STRING | BOOLEAN  
   type -> INTEGER | REAL | STRING | BOOLEAN | ARRAY int_constant OF type  
   int_constant -> DINT | OINT  
   literal_constant -> STR | TRUE | FALSE | neg number  
   number -> DINT | OINT | FLOAT | SCIENT  
   neg -> '-' | ε

5. 再來是 function的宣告跟定義(function_declaration和function_definition)

   function_declaration -> ID '(' arguments ')' ':' scaler_type ';' | ID '(' arguments ')' ';'

   function_definition -> ID '(' arguments ')' ':' scaler_type compound_statement END | ID '(' arguments ')' compound_statement END

   其中的 arguments可以產生多個參數  
   arguments -> ε | arguments1  
   arguments1 -> arguments1 ';' arg | arg   
   arg -> id_list ':' type   	
   id_list -> id_list ',' ID | ID  	

6. statement的部分有下列幾種statement: simple statement、conditional statement、while statement、for statement、return statement、procedure call statement
   對應的規則如下:

   simple_statement -> variable_reference ASSIGN expression ';'   
   simple_statement - > PRINT variable_reference ';'   
   simple_statement - > PRINT expression ';'   
   simple_statement - > READ variable_reference ';'   
   conditional_statement -> IF expression THEN compound_statement ELSE compound_statement END IF  
   conditional_statement -> IF expression THEN compound_statement END IF     
   while_statement -> WHILE expression DO compound_statement END DO  
   for_statement -> FOR ID ASSIGN int_constant TO int_constant DO compound_statement END DO  
   return_statement -> RETURN expression ';'  
   procedure_call_statement -> ID '(' more_expression ')' ';'

   上述幾條規則中，會用到以下幾個nonterminal的rule  
   variable_reference -> ID | ID array_reference  
   array_reference -> array_reference '[' expression ']' | '[' expression ']'  
   more_expression -> ε | more_expression1  
   more_expression1 -> expression | more_expression1 ',' expression  

   再來是compound statements，compound statements可以生一些變數的宣告和多個上述的statements，規則如下

   compound_statement -> Begin v_and_c_declaration statements END  	
   statements -> ε | statements1  
   statements1 -> statements1 statement_union | statement_union  
   statement_union -> simple_statement | conditional_statement | while_statement | for_statement 
   statement_union -> return_statement | procedure_call_statement | compound_statement

7.最後是expressions，也是我覺得最麻煩的地方  
  先寫出合理的運算的規則:

e -> '-' e| e '-' e | e '*' e | e '/' e | e MOD e | e '+' e | e LT e | e LE e | e LG e | e GE e | e GT e | e EQ e | e AND e | e OR e | NOT e | NOT | '(' e ')'

  由於這樣寫會造成ambiguity，所以要設定left associativity

  再來是expressions也可以包含變數、constant、和function invocations
  所以也會有下列的rules  
  e -> literal_constant | variable_reference | function_invocations  
  function_invocations: ID '(' exp ')'  
  exp -> ε | exp1  
  exp1 -> exp1 ',' expression | expression



## What is the hardest you think in this project

由於有上一次作業的經驗，再加上教授上課的內容，讓我對這次的作業可以更快了解要做的是甚麼。而在這次作業中，我覺得最難的部分是expression的rules，其中一個原因是expression的說明中的例子比較少，所以有一些部分我一開始不太懂，再來是expression如果依照直覺寫的話很容易有conflict，要想一些方式消除conflict，像是設定left-associative……等等。再來讓我覺得很困難的部分是消除conflict，yacc是實作LALR，我寫的grammer用LALR實作有一些conflict，雖然測資都有過，但我還是想試試看能不能消除所有的conflict，結果最後還是沒辦法全部消除。

## Feedback to T.A.s

我覺得在一些rule說明的部分，可以再多一些例子，有一些規則只有用文字說明，所以在看的時候會沒注意到，像是Expressions，希望助教可以在spec中再放多一點例子，可以讓我們在讀規則時更快了解規則在說什麼。
