===================================================
TASK 7: POLYNOMIAL CLASS AND ROOT FINDING (C++)
===================================================

OBJECTIVE:
----------
- Implement a Polynomial class that supports:
  1. Addition
  2. Subtraction
  3. Multiplication
  4. Evaluation at a given x
  5. Derivative
  6. Root-finding using Newton-Raphson method

---------------------------------------------------
CLASS: Polynomial
---------------------------------------------------

DATA:
-----
- coeffs: vector<double>
  Stores coefficients of the polynomial such that:
  coeffs[i] corresponds to the coefficient of x^i

CONSTRUCTOR:
------------
- Polynomial(vector<double> c)
  Initializes the polynomial with the provided coefficient list

FUNCTIONS:
----------

1. operator()(double x)
   - Evaluates the polynomial at x using Horner’s method

2. derivative()
   - Returns a new Polynomial which is the derivative:
     For each term a*x^i, the derivative is a*i*x^(i-1)

3. operator+(Polynomial other)
   - Adds two polynomials by adding corresponding coefficients

4. operator-(Polynomial other)
   - Subtracts corresponding coefficients

5. operator*(Polynomial other)
   - Multiplies two polynomials using nested loops
     result[i + j] += a[i] * b[j]

6. print()
   - Prints polynomial in human-readable form
     E.g., +1*x^2 -4

---------------------------------------------------
FUNCTION: findRootNewton()
---------------------------------------------------

Implements the **Newton-Raphson method**:
- x_{n+1} = x_n - f(x_n) / f'(x_n)

PARAMETERS:
- f: the polynomial
- guess: initial value
- tol: tolerance for stopping
- maxIter: max iterations

LOGIC:
1. Evaluate f(x) and f’(x)
2. Compute next x
3. If change is smaller than tol, return as root
4. If f’(x) ≈ 0, throw error (division by zero risk)
5. If no convergence in maxIter, throw error

---------------------------------------------------
MAIN FUNCTION: TEST CASES
---------------------------------------------------

EXAMPLE 1:
----------
f(x) = x^2 - 4
→ Roots: ±2
Initial guess = 2.0

Expected output:
Root near 2: 2 → f(2) = 0

EXAMPLE 2:
----------
f(x) = x^3 - 2x + 1
Initial guess = -1.5

Expected root near: -1.61803
f(root) ≈ 0

OTHER OPERATIONS:
-----------------
- sum = p1 + p2
- product = p1 * p2

These are also printed using print()

---------------------------------------------------
OUTPUT EXAMPLE:
---------------------------------------------------

Polynomial 1: +1*x^2 -4
Root found near 2: 2 → f(2) = 0

Polynomial 2: +1*x^3 -2*x +1
Root near -1.5: -1.61803 → f(-1.61803) = 1.55344e-07

Sum: +1*x^3 +1*x^2 -2*x -3
Product: +1*x^5 -2*x^4 -3*x^3 +8*x^2 -8*x -4

---------------------------------------------------
HOW TO COMPILE AND RUN:
---------------------------------------------------

Compile:
  g++ -std=c++17 Task7.cpp -o poly

Run:
  ./poly

---------------------------------------------------
HOW TO MODIFY FOR TESTING:
---------------------------------------------------

- Change polynomial coefficients in main()
- Test with linear (e.g. x - 5), quadratic, or cubic equations
- Try different initial guesses for root finding
- Use polynomial.print() to visualize expressions

---------------------------------------------------
ADVANTAGES:
-----------
- Fully generic polynomial operations
- Clean abstraction and reusable class
- Newton-Raphson allows fast root finding
- Uses C++17 standard features
- Good test coverage in main()

---------------------------------------------------
CONCEPTS COVERED:
------------------
- Operator overloading
- Class design
- Derivatives
- Polynomial arithmetic
- Newton-Raphson numerical method
- Exception handling
- Precision tolerance
- Function pointers and lambdas

