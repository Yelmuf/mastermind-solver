#include <stdio.h>
#include <stdbool.h>

#define MINIMAX_TURNOFF 5000

long pow(int a, int b) {
  /// Power for integers
  if (b == 0) {
    return 1;
  } else if (b == 1) {
    return a;
  } else {
    long r = a;
    for (int i = 1; i < b; i++)
      r = r * a;
    return r;
  };
}

long min(long a, long b) { return a < b ? a : b; }

int inputCP(int def) {
  /// Handle input of number from 2 to 10
  // TODO: deal with scanf() overflow
  int n = 0, s = 0;
  while (1) {
    s = scanf("%i", &n);
    if (n > 1 && n < 11) {
      return n;
    } else if (s) {
      printf("[!] Please enter number from 2 to 10\n");
    } else {
      printf("[!] Your input may have caused overflow. Using default number "
             "(%i)\n",
             def);
      break;
    }
  }
  return def;
}

bool handleInput(long input, int m, int p) {
  /// Return true if proper number is being input (base m, length p)
  for (int i = 0; i < p; ++i) {
    long num = input / pow(10, p - i - 1);
    if (num >= m || num < 0)
      return 0;
    input -= num * pow(10, p - i - 1);
  }
  return 1;
}

int testCode(long guess, long code, int p) {
  /// Test code for # of black and white pegs
  /// Returns # of black and white pegs
  int g[p];
  int c[p];
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
  int occurring[11] = {0};
  for (int i = 0; i < p; ++i) {
    occurring[g[i]]++;
  }
  int occurringC[11] = {0};
  for (int i = 0; i < p; ++i) {
    occurringC[c[i]]++;
  }
  for (int i = 0; i < 11; ++i) {
    occurring[i] = min(occurring[i], occurringC[i]);
  }

  int blacks = 0;
  for (int i = 0; i < p; ++i) {
    if (g[i] == c[i]) {
      blacks++;
      occurring[g[i]]--;
    }
  }
  int whites = 0;
  for (int i = 0; i < 11; ++i) {
    if (occurring[i] != 0)
      whites += occurring[i];
  }

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

long countActive(bool *active, long length) {
  long count = 0;
  for (long i = 0; i < length; ++i) {
    if (active[i])
      count++;
  }
  return count;
}

void initArrayFromZero(long *a, long length, int m) {
  /// Recursively initialize array [{0..m},{1..m},{2..m} ... {n..m}]
  for (long i = 0; i < length; i++) {
    a[i] = composeNum(i, m);
  }
}

long testNumber(long testingNumber, long *b, long length, bool *active, int p) {
  /// Find maximum score of number to test:
  /// https://programmingpraxis.com/2009/11/20/master-mind-part-2/
  long maximum = 0;
  for (long i = 0; i < p*10; i++) {
    long counter = 0;
    bool f = (composeNum(i, 5) / 10 + composeNum(i, 5)) < 5;
    for (long j = 0; j < length; j++) {
      if (active[j] && f) {
        if (testCode(testingNumber, b[j], p) == composeNum(i, 5)) {
          counter++;
        }
      }
    }
    if (counter > maximum) {
      maximum = counter;
    }
  }

  return maximum;
}

void setNumbersWithSameCodeActive(long number, long code, long *b, long length,
                                  bool *active, int p) {
  /// For each number with the same # of blacks and whites set "active"
  for (long i = 0; i < length; ++i) {
    if (testCode(b[i], number, p) == code) {
      active[i] = 1;
    } else {
      active[i] = 0;
    }
  }
}

void excludeNumbersWithSameCode(long number, long code, long *b, long length,
                                bool *active, int p) {
  /// For each number with not the same # of blacks and whites set "not active"
  for (long i = 0; i < length; ++i) {
    if (active[i] && (testCode(b[i], number, p) != code)) {
      active[i] = 0;
    }
  }
}

long firstActive(long *b, long length, bool *active, int p) {
  /// This does what you think it does
  long minimum = -1;
  long minimumNumber = -1;
  for (long i = 0; i < length; ++i) {
    if (active[i]) {
      minimum = testNumber(b[i], b, length, active, p);
      minimumNumber = b[i];
      return minimumNumber;
    }
  }
  return minimumNumber;
}

long minimax(long *b, long length, bool *active, int p) {
  /// Minimax explanation:
  /// https://programmingpraxis.com/2009/11/20/master-mind-part-2/

  // Set initial minimum
  long minimumNumber = firstActive(b, length, active, p);
  long minimum = testNumber(minimumNumber, b, length, active, p);

  // Apply minimax
  for (long j = 0; j < length; j++) {
    if (!active[j])
      continue;
    else {
      long localMaximum = testNumber(b[j], b, length, active, p);
      if (localMaximum < minimum) {
        minimum = localMaximum;
        minimumNumber = b[j];
      }
      printf("\r    [%li] minimum: %li minimax: %li", j, minimum, minimumNumber);
    }
  }

  printf("\n");
  return minimumNumber;
}

void printResult(long result) {
  /// This does what you think it does
  printf("\nYour number is %li.\nGGWP\n\n", result);
}

int main() {
  printf("x-----------------------------------------------------x\n");
  printf("|     Welcome to mastermind-solver demonstration!     |\n");
  printf("x-----------------------------------------------------x\n\n");

  printf("Enter number of colors: ");
  int m = inputCP(6); // {0,1,2,3,4,5} = 6 colors, 10 is maximum
  printf("Enter number of places: ");
  int p = inputCP(4); // 0052 = 4 places (digits), higher is slower

  printf("\nNow playing with %i colors and %i places\n", m, p);

  long length = pow(m, p); // 6^4 possibilities

  // Initialization of possibilities
  bool active[length]; // array of booleans to exclude in next search
  long b[length];
  initArrayFromZero(b, length, m);

  printf("Initialized %li possibilities\n", length);
  printf("Array tail: ");
  for (int i = 5; i > 0; i--) {
    printf("%li ", b[length - i]);
  }
  printf("\n");
  if (length > MINIMAX_TURNOFF) {
    printf("[i] Minimax is partly turned off to increase speed\n");
  }

  // Handle input
  long input;
  printf("\nEnter your combination:\n");
  scanf("%li", &input);
  while (!handleInput(input, m, p)) {
    printf("[!] Wrong code format, check number of colors and places, then "
           "enter code again:\n");
    scanf("%li", &input);
  }

  // According to the Donald Knuth's 5-steps algorithm, first guess should be
  // 1122 (or 0011 in our system) for 4 places,
  // which is minimax number at start. You can change it to number you want or
  // to look for it dynamically.
  // So we generate first code according to number of places,
  // e.g. 111222 for p=6 (000111 in our system)
  long teste = 0;
  for (int i = 0; i < p/2; i++) {
    teste += 1*pow(10,i);
  }

  // for (long i = 0; i < length; i++) {
  //   active[i] = 1;
  // }
  // long teste = minimax(b, length, active, p);

  for (int krok = 1; krok <= 10; krok++) {


    printf("\n[%i] Testing code %li\n", krok, teste);

    int r = testCode(teste, input,
                     p); // Result is numbers of white and black pegs (hits) for
                         // current test code (teste now)

    // Game lost if number of guesses exceeds 10
    // Cycle breaks if the code is found (p*10 stands for p black pegs and 0
    // whites)
    if (r == p * 10) {
      printResult(teste);
      break;
    }

    printf("    It's not an answer!");
    if (krok == 10) {
      printf("\n\nWe lost.\n");
      return 0;
    }

    printf(" Searching numbers to choose from ");
    if (krok == 1)
      printf("all");
    else
      printf("%li", countActive(active, length));
    printf(" active..\n    Excluding (%li, %i ...)\n", teste, r);

    if (krok == 1)
      setNumbersWithSameCodeActive(teste, r, b, length, active, p);
    else
      excludeNumbersWithSameCode(teste, r, b, length, active, p);

    long newTeste;
    if (countActive(active, length) < MINIMAX_TURNOFF) {
      // Apply the minimax rule to select next code to test
      printf("    Applying minimax...\n");
      newTeste = minimax(b, length, active, p);
    } else {
      // Turn off minimax for big numbers to inrease speed,
      // but will need more steps
      newTeste = firstActive(b, length, active, p);
    }

    if (newTeste == teste) {
      printf("\n[E] Opps, got into an infinite loop, please report to "
             "author\nExiting immediately\n");
      return 8;
    }

    teste = newTeste;
  }
  return 0;
}
