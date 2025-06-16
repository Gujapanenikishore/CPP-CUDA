/*Task 2: Expression Evaluator (Individual)

Implement a parser and evaluator for arithmetic expressions containing parentheses and standard operators (+, -, *, /).

Support correct operator precedence and associativity.

Provide detailed test cases demonstrating correct evaluations.*/ 


#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>
#include <map>
using namespace std;

// Operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Apply operator to two numbers
double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw runtime_error("Division by zero");
            return a / b;
    }
    throw runtime_error("Unknown operator");
}

// Evaluate expression using stacks
double evaluate(const string& expr) {
    stack<double> values;
    stack<char> ops;
    istringstream in(expr);
    char token;
    while (in >> token) {
        if (isdigit(token) || token == '.') {
            in.putback(token);
            double val;
            in >> val;
            values.push(val);
        }
        else if (token == '(') {
            ops.push(token);
        }
        else if (token == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            if (!ops.empty()) ops.pop();  // Remove '('
        }
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            ops.push(token);
        }
    }

    // Apply remaining operators
    while (!ops.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(a, b, op));
    }

    return values.top();
}

// ------------ Test Cases ------------
void runTests() {
    map<string, double> tests = {
        {"2 + 4 * 3", 14},
        {"(3 + 4) * 1", 7},
        {"7 + 3 * (10 / (12 / (3 + 1) - 1))", 22},
        {"(1 + 2) * (3 + 4)", 21},
        {"10 + (6 / 3)", 12},
        {"(5 + 3) * ((2 + 1) * 2)", 48},
        {"(7 - 2) * 3 + 1", 16},
        {"100 / (5 * (2 + 3))", 4},
        {"3.5 + 4.5 * 3", 17.0},
        {"(2 + 3.0) * 2", 10}
    };

    cout << "Running test cases:\n";
    for (const auto& [expr, expected] : tests) {
        try {
            double result = evaluate(expr);
            cout << expr << " = " << result;
            if (abs(result - expected) < 1e-6)
                cout << "  Passed";
            else
                cout << "  Failed (Expected: " << expected << ")";
            cout << endl;
        } catch (const exception& e) {
            cout << expr << "  Error: " << e.what() << endl;
        }
    }
}

// ------------ Main ------------
int main() {
    runTests();

    cout << "\nEnter your own expression (or type 'exit'): ";
    string input;
    while (getline(cin, input)) {
        if (input == "exit") break;
        try {
            double result = evaluate(input);
            cout << "Result = " << result << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
        cout << "\nEnter another expression (or 'exit'): ";
    }

    return 0;
}


/*___________--------
examples expressions 

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
7.2 - 3.1 + 1.9 */