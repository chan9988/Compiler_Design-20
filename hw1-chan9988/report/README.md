# hw1 report

|Field|Value|
|-:|:-|
|Name|詹凱傑|
|ID|0716049|

## How much time did you spend on this project

4.5 hours

## Project overview

這次的作業是要我們用lex來實作scanner，以下說明一些實作的細節:

在delimiter、Operator、Keywords的部分在regular expression直接用雙引號內放要辨識的字串。
ex: array就直接用 "array"

在identifiers的部分，用[a-zA-Z][0-9a-zA-Z]*表示，因為identifiers最一開始不能是數字，所以先用[a-zA-Z]來配對。

在integer的部分，分成decimal和Octal，decimal用[1-9][0-9]*|
[0]表示，Octal用[0][0-7]*表示。

float的部分用(0|[1-9][0-9]*)\.(0|[1-9]*[1-9])表示。

scientific Notations用({dec}|{flo})(E|e)(\+|\-)??{dec}，其中dec表示decimal integer，flo表示float。

然後再string的部分用\"([^\"\n]|\"\")*\"表示，用雙引號包起來的字串，中間可以包含兩個雙引號在一起，但不能只有一個單引號，才會符合條件，最後再透過c code把多的引號拿掉。

whitespace&tab用[ ]|\t來配對。

command的部分，先判斷是不是Pseudocomments，是的話將opt_src或opt_src改成正確的值，再來判斷是不是單行註解，用"//".* 來比對，最後，多行註解則用上課教的state來實作，如果讀到"/*"
就進到註解的state，而在註解的state讀到"*/"，就回到initial state。 


心得：
雖然在正規語言概論的課程中，有學過regular expression，且很多地方都會運用到regular expression，但我之前大多是讀別人寫的RE，很少有機會自己寫到。所以這次的作業讓我有機會自己用RE寫一些規則，來實做compiler的第一個步驟，我覺得學到非常多，特別是在聽完教授上課的內容之後，有一些實做的機會讓我對課程有更深入的了解。

## What is the hardest you think in this project

一開始看到spec時，因為內容很長，以為很難，但花了一點時間讀完，以及結合老師上課教的內容後，就知道要做什麼事了。
我覺得最難的部分是處裡command以及string的處裡。command的部分是一開始我是用$s，但我發現沒辦法達到我要的效果，後來上網找了一下後才發現有$x可以用；然後在單行註解的部分，我一開始是用"//.*"表示，但一直有錯，後來我才發現是我的表示法錯了，應該要用"//".*表示。然後再string的部分，開始一直想要怎麼用regular expression表示所敘述的，後來才想到可以用c來做字串處理。我想這兩部分是我覺得最難的地方。

## Feedback to T.A.s

> Please help us improve our assignment, thanks.

這次的作業中，在basic_cases中的第10筆測資，總共有4行comment，但解答只有印出3行，沒有印出 4: // comment，我覺得是跟最後有沒有\n有關係，不確定助教是不是故意這樣設計的？
