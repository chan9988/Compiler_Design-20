# hw4 report

|||
|-:|:-|
|Name|yourname|
|0716049|詹凱傑|

## How much time did you spend on this project

3 days.

## Project overview

這次的作業是要透過上次作業建立好的AST，對code做語法分析。以下對每個不同類型的Node做說明:

1. `ProgramNode`:
   1. push 一個新的 table 到 symbol table manager。
   2. 再 push 一個 entry 到 symbol table manager 中最上層的 table。
   3. 接下來去 visit chlid nodes。
   4. 若有需要 Dump symbol table 則將最上層的 table 印出來。
   5. 將最上層的 table pop 掉。

2. `DeclNode`:

   1. visit chlid nodes。

3. `VariableNode`:

   1. 先檢查這個變數有沒有被宣告過。
   2. 若這個變數是array ，看參數是不是大於零。
   3. 若第一個檢查沒過，則不會 push 一個 entry 到 symbol table manager 中最上層的 table ， 但若是第二個檢查沒過，還是會 push 一個 entry 到 symbol table manager 中最上層的 table ，但會將這個變數表示為不可用。
   4. visit chlid nodes。
   5. 兩個檢查都過則push 一個可用的 entry。

4. `CompoundStatementNode`:

   1. 看這個 compoundstatementnode 是不是接 functoin 底下，不是的話 push 一個新的 table 到 symbol table manager。
   2. visit chlid nodes。
   3. 若有需要 Dump symbol table 則將最上層的 table 印出來。
   4. 將最上層的 table pop 掉。

5. `ConstantValueNode`:

   1. 先判斷是不是constant variable的值，來決定要不要更新symbol table 的 entry。
   2. 再來是將 constant 的資訊傳給 expression 中的 type ( constant 從 expression繼承而來 )。

6. `FunctionNode`:

   1. 先檢查這個函式有沒有被宣告過。
   2. 沒宣告過就新增一個 entry 到 symbol table manager 中最上層的 table 。
   3. push 一個新的 table 到 symbol table manager。
   4. visit chlid nodes。
   5. 若有需要 Dump symbol table 則將最上層的 table 印出來。
   6. 將最上層的 table pop 掉。

7. `PrintNode`:

   1. visit chlid nodes。
   2. 先確定 print target 是不是沒有錯誤。
   3. 然後在檢查 print target 的 type 是不是 array或 void，是的話就報錯。

8. `BinaryOperatorNode`:

   1. visit chlid nodes。
   2. 取的 left child跟 right child 的 type，並由 spec 的規則(不同operator的規則不同）比較兩個 type，若之間不能轉換就報錯。
   3. 將適當的 type 紀錄起來並傳到 expression 的 type。

9. `UnaryOperatorNode`:

   1. visit chlid nodes。
   2. 取的 operand 的 type，並由 spec 的規則(不同operator的規則不同）比較 type。
   3. 將適當的 type 紀錄起來並傳到 expression 的 type。

10. `FunctionInvocationNode`:

    1. visit chlid nodes。
    2. 先看呼叫的 function 有沒有宣告過，或是不是呼叫一個變數而不是函式。
    3. 若上方的檢查 ok 後，就從symbol table 找出被呼叫的 function 的arguments個數，然後比對呼叫時傳入的arguments 個數有沒有相同。
    4. 如果個數相同，就檢查type有沒有符合。

11. `VariableReferenceNode`: 

    1. 先看呼叫的 variable 有沒有宣告過
    2. 再檢查呼叫的是一個 variable kind。
    3. visit chlid nodes。
    4. 若這個變數是一個array ，則檢查 index 的個數是不是超過宣告的數量

12. `AssignmentNode`: 

    1. visit chlid nodes。
    2. 再來是檢查要被 assign 的 variable reference 是不是一個 array。
    3. 以及這個 variable reference 是不是被宣告成一個 constant。
    4. 以及這個 variable reference 是不是一個 loop_var。
    5. 再來是 assign 給 variable 的 expression， 檢查這個 expression 是不是一個 array type。
    6. 最後是這個 assign 兩邊的 type 是要相同，或是可以被轉換的。

13. `ReadNode`: 

    1. visit chlid nodes。
    2. 檢查要被傳入資料的變數是不是scalar type。
    3. 再來是檢查這個變數是不是一個for variable。

14. `IfNode`: 

    1. visit chlid nodes。
    2. 檢查 condition 的 type 是不是 boolean。

15. `WhileNode`: 

    1. visit chlid nodes。
    2. 檢查 condition 的 type 是不是 boolean。

16. `ForNode`: 

    1. visit chlid nodes。
    2. 檢查 lower bound 和 upper bound 是不是 incrementation。
       - 這部份是我覺的比較麻煩的，我的作法是在遇到 for 時，先在 stack manager 裡將 lower bound 記下來，在處理完 upper bound 後，再將兩個變數互相比較。

17. `ReturnNode`: 

    1. visit chlid nodes。
    2. 若要 return 的是一個 function ，要確定這個 function 的 return type 是不是 void。
    3. 再來，我有在 stack manager 裡 maintain 一個 vector ，來紀錄現在在哪個 function 裡，而遇到 return 時，要檢查 return type 個這個 function 的 return type 有沒有相同。


## What is the hardest you think in this project

在這次作業中，我覺得最難的有以下幾個部分:

1. 首先，我是用助教給的hw3的sample solution來改寫的，沒有用我之前寫的版本，所以有一些參數要從chlid傳到parent時，不太了解助教寫的意思，花了一些時間研究才懂。而參數的傳遞是我覺得最難的部分，也是這次作業的重點，特別是有一些型別是array，所以處理起來有複雜很多。

2. 再來是symbol table的部分，由於第一個test case就要建立symbol table，而就symbol的過程也不會太複雜，但我建立好後，我好像不太會用，我覺得是我symbol table的資料結構沒有設計很好，所以很多時候還是要到child找資料，沒辦法直接從table就得到我要的資料。我想這部分也讓我有些分析變得比較麻煩。

3. 最後是在處理不同node時要做的檢查，由於有上一次作業的經驗，這次很快就知道要從哪裡下手，但這次作業跟前幾次不太一樣的地方是每個node都有自己的規則，不童的node有各自的規則，且有些規則還蠻複雜的，規則的順序也有差，這部分我也覺得是蠻複雜的部份。

## Feedback to T.A.s

首先是hw3的sample solution，由於助教給的code有用到很多unique_ptr、shared_ptr之類的指標，我查了之後發現是c++ 11後才有的，對我來說是第一次接觸，讓我覺得還蠻新鮮的，但為了用懂這方面的運作原理也花了我一些時間。希望助教可以解釋一下sample solution的資料結構，以及這些指標是如何運作的，雖然這很像更這次作業比較沒關係，但如果能夠說明一下會讓我們對這次作業要如何處理資料會更有想法。

在測資的部分我覺得這次的測資能夠明確的讓我知道我錯在哪裡，算是幫我省的很多時間，不過在spec的部分，雖然spec有說我們要做怎樣的檢查，但大多只是文字說明而已，希望spec裡的說明可以增加一些實際的例子。

最後是做完這次的作業後(以及上次的作業)，我才知道semantic analysis原來這麼複雜，特別是在型別檢查方面，我本以為只是看看兩個type有沒有相同而已，但在聽完教授的課後，以及自己實作一遍之後，我才發現要考慮很多細節，是我之前沒注意到的，不過在做完這兩次作業後，也讓我對semantic analysis有更深的認識。


