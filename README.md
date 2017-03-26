# mastermind-solver     [![Build Status](https://travis-ci.org/Yelmuf/mastermind-solver.svg?branch=master)](https://travis-ci.org/Yelmuf/mastermind-solver)
Implementation of slightly modified Donald Knuth's five-guess algorithm in C/C++

Based on
* [Mastermind game on Wikipedia](http://en.wikipedia.org/wiki/Mastermind_(board_game))
* [Explanation of list of possible solutions StackExchange](http://math.stackexchange.com/a/1193037)
* [Explanation of minimax search on ProgrammingPraxis](http://programmingpraxis.com/2009/11/20/master-mind-part-2/)

Dependencies
* g++-4.9
* cmake-3.6

Input | Output  
--- | ---  
The code for algorithm to guess | Number of guess iterations  

#### Sample output:
<pre>
x---------------------------------------x  
|     Welcome to mastermind-solver!     |  
x---------------------------------------x  
Now playing with 6 colors and 4 places  
Initialized 1296 possibilities  
Array tail: 5551 5552 5553 5554 5555   

Enter your combination:  
5143  

Here's a starting minimax: 11  

[1] Testing code 11  
    It's not an answer! Searching numbers to choose from all active..  
    Excluding (11, 1... )  
    new minimax<-1223   
[2] Testing code 1223  
    It's not an answer! Searching numbers to choose from 256 active..  
    Excluding (1223, 11... )  
  
[3] Testing code 1334  
    It's not an answer! Searching numbers to choose from 51 active..  
    Excluding (1334, 3... )  
  
[4] Testing code 3153  
    It's not an answer! Searching numbers to choose from 4 active..  
    Excluding (3153, 21... )  
  
[5] Testing code 5143  
  
Your number is 5143  
GGWP  
</pre>
