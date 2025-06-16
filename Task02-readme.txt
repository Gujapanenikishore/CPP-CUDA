==========================================
TASK 2: EXPRESSION EVALUATOR (C++)
==========================================

OBJECTIVE:
----------
To implement a mathematical expression evaluator in C++ that supports:

- Operators: +, -, *, /
- Parentheses ()
- Floating point and integer values
- Correct operator precedence and associativity
- User input and test cases

-------------------------------------------
LOGIC OVERVIEW:
-------------------------------------------

1. Use two stacks:
   - `values` stack: stores operands (numbers)
   - `ops` stack: stores operators and parentheses

2. The expression is parsed character-by-character:
   - If the token is a digit or decimal: read full number and push to `values`
   - If token is '(': push to `ops`
   - If token is ')': pop from `ops` and apply operations until '(' is found
   - If token is an operator (+ - * /):
     - Check precedence with top of `ops`
     - Apply higher/equal precedence ops from stack first
     - Then push current operator

3. After parsing:
   - Apply remaining operators from the stack

4. The final result will be on top of `values` stack

-------------------------------------------
FUNCTIONS:
-------------------------------------------

int precedence(char op):
- Returns precedence:
  + and - = 1
  * and / = 2

double applyOp(double a, double b, char op):
- Applies a binary operation
- Handles division by zero

double evaluate(const string& expr):
- Uses stacks to evaluate the full expression

-------------------------------------------
TEST CASES:
-------------------------------------------

The function runTests() checks the evaluator with sample expressions:

Examples:
----------
"2 + 4 * 3"                        => 14
"(3 + 4) * 1"                      => 7
"7 + 3 * (10 / (12 / (3 + 1) - 1))" => 22
"(1 + 2) * (3 + 4)"               => 21
"10 + (6 / 3)"                    => 12
"(5 + 3) * ((2 + 1) * 2)"         => 48
"(7 - 2) * 3 + 1"                 => 16
"100 / (5 * (2 + 3))"             => 4
"3.5 + 4.5 * 3"                   => 17
"(2 + 3.0) * 2"                   => 10

The result is compared with expected output using a tolerance of 1e-6.

-------------------------------------------
USER INPUT SUPPORT:
-------------------------------------------

After test cases, the program prompts:
"Enter your own expression (or type 'exit'):"

The user can:
- Enter a valid expression to evaluate it
- Type 'exit' to terminate the loop

-------------------------------------------
ERROR HANDLING:
-------------------------------------------

- If a divide-by-zero occurs, prints:
  "Error: Division by zero"

- If an unknown operator or invalid input is used:
  prints appropriate exception message

-------------------------------------------
EXPRESSION EXAMPLES FOR TESTING:
-------------------------------------------

(5 + 3) * 2
(10 / (2 + 3)) + 7
3.5 + 4.5 * 2
(4 + 6) * 2
10 + 2 * 5
(15 / 3) + (2 * 4)
(3 + 2) * (7 - 4)
18 - 6 / 2
5 * (3 + 2) - 4
((1 + 2) * (3 + 4)) / 2
20 / (2 + 3)
(2.5 + 1.5) * 4
7.2 - 3.1 + 1.9

-------------------------------------------
COMPILATION AND EXECUTION:
-------------------------------------------

To compile:
  g++ -std=c++17 Task2.cpp -o evaluator

To run:
  ./evaluator

The program will display test results and allow you to enter more expressions.

-------------------------------------------
SUMMARY OF CONCEPTS COVERED:
-------------------------------------------

- Stack-based parsing
- Operator precedence
- Associativity handling
- Floating-point arithmetic
- Exception safety
- User input parsing
- Unit testing using map of expressions

