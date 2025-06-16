===========================================
TASK 8: NUMERICAL INTEGRATION (C++)
===========================================

OBJECTIVE:
----------
To implement and compare two numerical integration techniques:
1. Trapezoidal Rule
2. Simpson’s Rule

Evaluate their accuracy against known analytical results.

-------------------------------------------
METHODS IMPLEMENTED:
-------------------------------------------

1. Trapezoidal Rule:
--------------------
Formula:
  ∫ f(x) dx ≈ h/2 * [f(a) + 2*f(x1) + ... + 2*f(x_{n-1}) + f(b)]

Code Logic:
- Divide [a, b] into n equal intervals of width h
- Approximate the area under the curve with trapezoids
- Add first and last values as is, multiply the rest by 2
- Multiply the sum by h/2

Function:
  double trapezoidal(const function<double(double)>& f, double a, double b, int n)

2. Simpson’s Rule:
------------------
Formula (n must be even):
  ∫ f(x) dx ≈ h/3 * [f(a) + 4*f(x1) + 2*f(x2) + ... + 4*f(x_{n-1}) + f(b)]

Code Logic:
- Similar to trapezoid but uses parabolic segments for more accuracy
- Alternates weights 4 and 2 for odd and even indices

Function:
  double simpson(const function<double(double)>& f, double a, double b, int n)

Note:
  - If n is odd, Simpson’s rule automatically increments n by 1

-------------------------------------------
TEST FUNCTIONS USED:
-------------------------------------------

1. f1(x) = sin(x)
   Interval: [0, π/2]
   Known integral: 1

2. f2(x) = x^3
   Interval: [0, 1]
   Known integral: 1/4 = 0.25

3. f3(x) = exp(-x^2)
   Interval: [0, 1]
   No exact analytical solution
   (Used for approximation test only)

4. f4(x) = log(1 + x)
   Interval: [0, 1]
   Known integral: ln(2) ≈ 0.38629436

-------------------------------------------
OUTPUT FORMAT:
-------------------------------------------

For each function:
- Method used (Trapezoidal / Simpson)
- Result from numerical method
- Analytical result (if available)

Example:
-------------------------------------------
Integrating sin(x) from 0 to pi/2:
Trapezoidal: 0.99999979
Simpson:     1.00000000
Analytical:  1.0
-------------------------------------------

-------------------------------------------
ACCURACY ANALYSIS:
-------------------------------------------

- Simpson’s rule is generally more accurate for smooth functions
- Trapezoidal is faster but less precise, especially on curved graphs
- For sin(x), x^3, log(1+x): Simpson gives exact or near-exact result
- For exp(-x^2), both give close approximations

-------------------------------------------
HOW TO COMPILE AND RUN:
-------------------------------------------

To compile:
  g++ -std=c++17 Task8.cpp -o integrate -lm

To run:
  ./integrate

-------------------------------------------
MODIFICATION OPTIONS:
-------------------------------------------

- Increase/decrease 'n' (e.g., 500, 2000) for precision tuning
- Replace or add more functions using lambda or named functions
- Change integration limits a and b to test different intervals
- Add error calculation logic to compare with analytical results

-------------------------------------------
CONCEPTS DEMONSTRATED:
------------------------

- Numerical integration
- std::function and function pointers
- Mathematical function implementation
- Fixed-point formatting with setprecision
- Benchmarking numerical vs analytical accuracy
- Adaptive logic (e.g., correcting Simpson's n to even)

