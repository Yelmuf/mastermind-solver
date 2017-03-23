#include <stdio.h>
#include <iostream> // only for cout

using namespace std;

int pow(int a, int b) {
    /// Power for integers
    if (b == 0) {
        return 1;
    } else if (b == 1) {
        return a;
    } else {
        int r = a;
        for (int i = 1; i < b; i++)
            r = r * a;
        return r;
    };
}

bool handleInput(long input, int m, int p) {
    for (int i = 0; i < p; ++i) {
        long num = input / pow(10, p - i - 1);
        // cout << "( num " << num << " < " << m << " ? )" << endl;
        if (num >= m || num < 0)
            return 0;
        input -= num * pow(10, p - i - 1);
    }
    return 1;
}

int testCode(long guess, long code, int p) {
    /// Test code for # of black and white pegs
    /// Returns # of black and white pegs
    int g[p] = {};
    int c[p] = {};
    // Decompose a number to p numbers by their places
    for (int i = 0; i < p; ++i) {
        g[i] = guess / pow(10, p - i - 1);
        guess -= g[i] * pow(10, p - i - 1);
        c[i] = code / pow(10, p - i - 1);
        code -= c[i] * pow(10, p - i - 1);
    }
    // Create array of occurring numbers
    // 0 - no occurrence,
    // 1 - only color
    // 2 - color and place
    int occurring[10] = {0};
    for (int i = 0; i < p; ++i) {
        occurring[g[i]]++;
    }
    int occurringC[10] = {0};
    for (int i = 0; i < p; ++i) {
        occurringC[c[i]]++;
    }
    for (int i = 0; i < 10; ++i) {
        occurring[i] = min(occurring[i], occurringC[i]);
    }

//    // debug
//    cout << "testCode(";
//    for (int j = 0; j < p; ++j) {
//        cout << g[j];
//    }
//    cout << ",";
//    for (int j = 0; j < p; ++j) {
//        cout << c[j];
//    }
//    cout << ")__" << endl;
//    cout << "occurring: ";
//    for (int i = 0; i < 10; ++i) {
//        cout << occurring[i] << " ";
//    }
//    // debug end

    int blacks = 0;
    for (int i = 0; i < p; ++i) {
        if (g[i] == c[i]) {
            blacks++;
            occurring[g[i]]--;
        }
    }
    int whites = 0;
    for (int i = 0; i < 10; ++i) {
        if (occurring[i] != 0)
            whites += occurring[i];
    }

//  // debug return
//    cout << endl << "__return " << blacks*10 + whites
//         << " (" << blacks << " blacks and " << whites << " whites)" << endl;
    return blacks * 10 + whites;
}

long composeNum(long j, int m) {
    /// Translate number j from decimal into a numeral system with base m
    long r = j % m;
    long b = j / m;
    int d = 1;
    while (b != 0) {
        r += (b % m) * pow(10, d);
        b = b / m;
        d++;
    }
    return r;
}

int countActive(bool *active, int length) {
    int count = 0;
    for (int i = 0; i < length; ++i) {
        if (active[i])
            count++;
    }
    return count;
}

void initArrayFromZero(long *a, int n, int m) {
    /// Recursively initialize array [{0..m},{1..m},{2..m} ... {n..m}]
    for (int i = 0; i < n; i++) {
        a[i] = composeNum(i, m);
    }
}

int testNumber(long testingNumber, long *b, int length, bool *active, int p) {
    /// Find maximum score of number to test: https://programmingpraxis.com/2009/11/20/master-mind-part-2/
//    cout << "Testing number " << testingNumber << ":" << endl;
    int maximum = 0;
    for (int i = 0; i < 40; ++i) {
        int counter = 0;
        bool f = (composeNum(i, 5) / 10 + composeNum(i, 5)) < 5;
        for (int j = 0; j < length; ++j) {
            if (!active[i] && f) {
                if (testCode(testingNumber, b[j], p) == composeNum(i, 5)) {
                    counter++;
                }
            }
        }
        if (counter > maximum)
            maximum = counter;
//        cout << counter << endl;
    }
//    cout << "max: " << maximum << endl;
    return maximum;
}


void setNumbersWithSameCodeActive(long number, long code, long *b, int length, bool *active, int p) {
    /// For each number with the same # of blacks and whites set "active"
    for (int i = 0; i < length; ++i) {
        if (testCode(b[i], number, p) == code) {
            active[i] = 1;
        }
    }
}


void excludeNumbersWithSameCode(long number, long code, long *b, int length, bool *active, int p) {
    /// For each number with not the same # of blacks and whites set "not active"
    for (int i = 0; i < length; ++i) {
        if (active[i] && (testCode(b[i], number, p) != code)) {
            active[i] = 0;
        }
    }
}

int minimax(long *b, int length, bool *active, int p) {
    /// Minimax explanation: https://programmingpraxis.com/2009/11/20/master-mind-part-2/
    long minimum = -1;
    int minimumNumber = -1;
    // set initial minimum11
    int i = 0;
    for (i; i < length; ++i) {
        if (active[i]) {
            minimum = testNumber(b[i], b, length, active, p);
            minimumNumber = b[i];
//            cout << "broke from min search loop with b[i] = " << b[i] << "[" << i << "]" << endl; // debug
            break;
        }
    }

    for (i; i < length; ++i) {
        if (!active[i])
            continue;
        else {
            int maximum = testNumber(b[i], b, length, active, p);
            if (minimum > maximum) {
                minimum = maximum;
                minimumNumber = b[i];
                cout << "    new minimax<-" << minimumNumber << " ";
            }
        }
    }
    return minimumNumber;
}

void printResult(long result) {
    /// This does what you think it does
    cout << endl << "Your number is ";
    printf("%li", result);
    cout << endl << "GGWP" << endl;
}


int main() {
    cout << "x---------------------------------------x" << endl;
    cout << "|     Welcome to mastermind-solver!     |" << endl;
    cout << "x---------------------------------------x" << endl;

    /// Change your rules here ////////////////////////////////////////////
    int m = 6; // {0,1,2,3,4,5} = 6 colors, // 10 is maximum             //
    int p = 4; // 0052 = 4 places (digits), // higher is slower          //
    ///////////////////////////////////////////////////////////////////////


    cout << "Now playing with " << m << " colors and " << p << " places" << endl;
    int length = pow(m, p); // 6^4 possibilities

    // Initialization of possibilities
    bool active[length] = {0}; // array of booleans to exclude in next search
    long b[length];
    initArrayFromZero(b, length, m);
    cout << "Initialized " << length << " possibilities" << endl;
    cout << "Array tail: ";
    for (int i = 5; i > 0; i--) {
        cout << b[length - i] << " ";
    }
    cout << endl;

//    cout << "// Some active testings: " << active[0] << " " << active[length/2] << " "
//         << active[length-1] << " (should be all zeros)" << endl;


    // Handle input
    long input;
    cout << endl << "Enter your combination:" << endl;
    scanf("%li", &input);
    while (!handleInput(input, m, p)) {
        cout << "Wrong code format, check number of colors and places, then enter code again:" << endl;
        scanf("%li", &input);
    }


    // According to the Donald Knuth's 5-steps algorithm, first guess should be 1122 (or 0011 in our system),
    // which is minimax number at start. You can change it to number you want or to look for it dynamically
    long teste = 11;
    // long teste = minimax(b, length, active, p); // 9 seconds on core-i5 for p=4, m=6, much more for bigger numbers

    cout << "Here's a starting minimax: " << teste << endl;


    for (int krok = 1; krok <= 10; krok++) {

        cout << endl << "[" << krok << "] Testing code " << teste << endl;

        int r = testCode(teste, input,
                         p); // Result is numbers of white and black pegs (hits) for current test code (teste now)

        // Game lost if number of guesses exceeds 10
        // Cycle breaks if the code is found (p*10 stands for p black pegs and 0 whites)
        if (r == p * 10) {
            printResult(teste);
            break;
        }

        cout << "    It's not an answer! Searching numbers to choose from ";
        if (krok == 1)
            cout << "all";
        else
            cout << countActive(active, length);
        cout << " active.." << endl << "    Excluding (" << teste << ", " << r << "... )" << endl;

        if (krok == 1)
            setNumbersWithSameCodeActive(teste, r, b, length, active, p);
        else
            excludeNumbersWithSameCode(teste, r, b, length, active, p);


        // Apply the minimax rule to select next code to test
        long newTeste = minimax(b, length, active, p);
        if (newTeste == teste) {
            cout << endl << "[E] Opps, got into an infinite loop, please report to author\nExiting immediately";
            return 3;
        }
        teste = newTeste;

    }

    return 0;
}
