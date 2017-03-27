# mastermind-solver     [![Build Status](https://travis-ci.org/Yelmuf/mastermind-solver.svg?branch=master)](https://travis-ci.org/Yelmuf/mastermind-solver)
Implementation of slightly modified Donald Knuth's five-guess algorithm in C/C++

(Program is written in study purposes to show the algorithm work)  

Based on
* [Mastermind game on Wikipedia](http://en.wikipedia.org/wiki/Mastermind_(board_game)#Five-guess_algorithm)
* [Explanation of list of possible solutions on StackExchange](http://math.stackexchange.com/a/1193037)
* [Explanation of minimax search on ProgrammingPraxis](http://programmingpraxis.com/2009/11/20/master-mind-part-2/)

Dependencies
* clang / cmake

Input | Output  
--- | ---  
The code for algorithm to guess | Number of guess iterations and code  

#### Sample output:
<pre>
x-----------------------------------------------------x
|     Welcome to mastermind-solver demonstration!     |
x-----------------------------------------------------x

Enter number of colors: 8 
Enter number of places: 5

Now playing with 8 colors and 5 places
Initialized 32768 possibilities
Array tail: 77773 77774 77775 77776 77777 
[i] Minimax is partly turned off to increase speed

Enter your combination:
76455

[1] Testing code 11
    It's not an answer! Searching numbers to choose from all active..
    Excluding (11, 0 ...)

[2] Testing code 22222
    It's not an answer! Searching numbers to choose from 7776 active..
    Excluding (22222, 0 ...)
    Applying minimax...
    [32767] minimum: 402 minimax: 334453

[3] Testing code 33445
    It's not an answer! Searching numbers to choose from 3125 active..
    Excluding (33445, 20 ...)
    Applying minimax...
    [32741] minimum: 9 minimax: 366755

[4] Testing code 36675
    It's not an answer! Searching numbers to choose from 194 active..
    Excluding (36675, 21 ...)
    Applying minimax...
    [32677] minimum: 0 minimax: 35565

[5] Testing code 35565
    It's not an answer! Searching numbers to choose from 33 active..
    Excluding (35565, 12 ...)
    Applying minimax...
    [32045] minimum: 0 minimax: 53775

[6] Testing code 53775
    It's not an answer! Searching numbers to choose from 5 active..
    Excluding (53775, 12 ...)
    Applying minimax...
    [32045] minimum: 0 minimax: 76455

[7] Testing code 76455

Your number is 76455.
GGWP

</pre>
