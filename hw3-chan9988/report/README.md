# hw3 report

|||
|-:|:-|
|Name|詹凱傑|
|ID|0716049|

## How much time did you spend on this project

e.g. 1.5 weeks .

## Project overview

這次的作業是要在parse的過程中產生Abstract Syntax Tree，方便我們之後的作業做一些分析。此外，我有實作visitor pattern，用visitor pattern來dump AST。

以下說明AST中夠種Node的結構:

1. `AstNode`: 
   - 最基本的Node，裡面有一個Location的structure來記錄位置資訊，之後的Node都是由繼承AstNode。

2. `ProgramNode`:
   - `name`: string，存放program的名子。 
   - `returntype`: string，存放return type。
   - `ch`: vector<AstNode *>，指向program的variable、function和compound statement 

3. `CompoundStatementNode`:
   - `decl`: vector<AstNode *>，指向compound statement中的declaration。
   - `stat`: vector<AstNode *>，指向compound statement中的statement。

4. `DeclNode`:
   - `ch`: vector<AstNode *>，指向declaration中的variable。

5. `VariableNode`:
   - `name`: char* ，變數名稱。
   - `type`: int，變數的型別，type=0,1,2,3分別對應到integer,real,string,boolean。
   - `arr`: vector<int*>，這個變數有可能是一個array，從放array的數值。
   - `intconstant`: int，若type=0，則將variable的值存放在此。
   - `doubleconstant`: double，若type=1，則將variable的值存放在此。
   - `str`: char *，若type=2 or type=3，則將variable的值存放在此。
   - `ch`: AstNode *，指向constant value。

6. `ConstantValueNode`:
   - `type`: int，變數的型別，type=0,1,2,3分別對應到integer,real,string,boolean。
   - `intconstant`: int，若type=0，則將variable的值存放在此。
   - `doubleconstant`: double，若type=1，則將variable的值存放在此。
   - `str`: char *，若type=2 or type=3，則將variable的值存放在此。
7. `FunctionNode`:
   - `name`: char* ，function的名稱。
   - `decl`: vector<AstNode *>，指向function中的declaration。
   - `returntype`: int，type=0,1,2,3,4分別對應到integer,real,string,boolean,void。
   - `arg`: vector<int>，存放function的input argument的type，type的類型同上方說明。
   - `ch`: AstNode *，指向一個compound statement。
8. `PrintNode`:
   - `ch`: AstNode *，指向一個expression。
9. `BinaryOperatorNode`:
   - `op` :char *，存放要做的operation，有些operation會用到不只一個char，所以用char *的方式存放。
   - `ex1`: 指向operator左邊的expression。
   - `ex2`: 指向operator右邊的expression。
10. `UnaryOperatorNode`:
    - `op` :char *，存放要做的operation。
    - `ex1`: 指向expression。
11. `FunctionInvocationNod`:
    - `name`: char*，被呼叫的function的名子。
    - `ch`: vector<AstNode *>，指向expression。
12. `VariableReferenceNode`:
    - `name`: char*，variable的名子。
    - `ex`: vector<AstNode *>，指向expression。
13. `AssignmentNode`:
    - `vr`: AstNode *，指向一個variable reference。
    - `ex`: AstNode *，指向一個expression。
14. `ReadNode`:
    - `vr`: AstNode *，指向一個variable reference。
15. `IfNode`:
    - `ex`: AstNode *，指向要做判斷的expression。
    - `cs1`: AstNode *，指向if底下的compound statement。
    - `cs2`: AstNode *，指向else底下的compound statement。
16. `WhileNode`:
    - `ex`: AstNode *，指向要做判斷的expression。
    - `cs`: AstNode *，指向while底下的compound statement。
17. `ForNode`:
    - `de`: AstNode *，指向for當中宣告的變數。
    - `as`: AstNode *，指向做完一次for後要做的assignment。
    - `ex`: AstNode *，指向要做判斷的expression。
    - `cs`: AstNode *，指向while底下的compound statement。
18. `ReturnNode`:
    - `ex`: AstNode *，指向一個expression。

#### 再來是加分題的部份:

1. 首先新增一個class，叫做AstDumper從AstNodeVisitor繼承而來，在這個class中定義許多visit的函式，當遇到不同的node要做怎樣的行為都定義在這個class，而這次的作業是想Node的資訊print出來。

2. 然後每個node新增兩的函式，分別是 accept和visitChildNodes。
    - `Accept`:這個 function 的 input是一個 AstNodeVisitor &，當這個 function 被呼叫後，會呼叫傳進來的 AstNodeVisitor 中的 visit 函式，並將自己的型別透過 (*this) 傳給 visit 的函式
    - `visitChildNodes`:這個function的input也是一個 AstNodeVisitor & ，而這個 function 會呼叫自己 child 的 accept 函式，並將 input 的 AstNodeVisitor 傳給 chile 的 accept 函式。

3. 在AstDumper的visit被呼叫後，做完print後，就再呼叫傳進來的Node中的visitChildNodes這個function。

4. 最後在 parse 完整個 code ，並產生一個 AST 後，呼叫root的accept，並將一個AstDumper傳進去，就可以透過visitor pattern的方式將整個tree dump出來。


## What is the hardest you think in this project

我覺得這次的作業比前面幾次難很多，所以遇到的困難也多很多。首先，我遇到的困難就是題目看很久才看懂，但這不是spec寫不清楚的問題，而是資訊量太大了，雖然我一開始就知道這次作業是要建立一個tree，但很多細節我研究很久後才懂，花了不少時間消化spec的內容。

再來第二個困難點是這次作業用的很多物件導向的東西，自從我OOP修完後到這次作業也快忘得差不多的，所以我還要花一些時間回想一下之前學的內容。

而讓我覺得最煩的是這次作業我用到很多pointer，所以一不小心沒有維護好就會segmentation fault，我記得我有一個segmentation fault找了快3小時才找到哪裡出問題，所以每次在測試的時候，只要一看到segmentation fault，就會覺得很煩，總覺得我一直在找bug，然後花很多時間才寫完。

最後，是加分題的部分，一開始我也大概能了解助教想要表達的內容，但我還是花了很多時間才弄懂visitor和Ast 的那些Node是如何做呼叫的。老實說，我中間看了很多次後，很多次都要放棄不做加分題了，特別是只改了一點後就不能編譯，不然就是segmentation fault，總覺得會做不出來。但想了一下老師說的，做出來後之後的作業會比較輕鬆，再加上到學期末我一定更忙，不如先在先花多一點時間，最後，我也是花了大概半天才把原本的版本改成visitor pattern的形式。


## Feedback to T.A.s

在做作業的過程中，由於這次有很多個node，且每個node又有宣告跟定義，每個宣告跟定義有放在不同的檔案裡，所以一次可能要開10多個檔案，特別是在debug時，需要開很多個檔案一起找，我覺得這樣有點麻煩，雖然這樣可以從檔名就找到需要的class，但或許把所以宣告寫在同一個檔案，再把所有定義寫在同一個檔案，也是不錯的方式。

再來是測資方面的問題，由於這次的有些測資會測式不同的node，像是第五筆，雖然是測print的測資，但當中會用到FunctionInvocationNode，由於我一開始只寫好print，還沒寫FunctionInvocation，然而這筆一直segmentation fault，所以我一直以為是print寫錯，後來才發現是FunctionInvocation的問題，希望助教可以將測資改成，前面的測資先一次多測一個node，後面的測資再測綜合的結果，或許這樣能夠讓我們更了解錯的地方在哪裡。

這次作業簡單來說就是建立一個tree，但在建的時候有很多細節要注意，且過程中遇到很多問題，花了很多時間，但完成後就覺得很有成就感，學到很多東西。

