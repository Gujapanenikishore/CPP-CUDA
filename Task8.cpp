#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

using namespace std;

// Trapezoidal Rule
double trapezoidal(const function<double(double)>& f, double a, double b, int n) {
    double h = (b - a) / n;
    double result = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < n; ++i) {
        result += f(a + i * h);
    }
    return result * h;
}

// Simpson's Rule (n must be even)
double simpson(const function<double(double)>& f, double a, double b, int n) {
    if (n % 2 != 0) {
        cerr << "Simpson's rule requires even n. Increasing n by 1." << endl;
        ++n;
    }
    double h = (b - a) / n;
    double result = f(a) + f(b);
    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        result += (i % 2 == 0 ? 2 : 4) * f(x);
    }
    return result * h / 3.0;
}

// Test functions
double f1(double x) { return sin(x); }             // Integral from 0 to pi/2: 1
double f2(double x) { return x * x * x; }          // Integral from 0 to 1: 1/4
double f3(double x) { return exp(-x * x); }        // No closed-form
double f4(double x) { return log(1 + x); }         // Integral from 0 to 1: ~0.38629436

void testIntegration() {
    cout << fixed << setprecision(8);
    int n = 1000;

    // f1: sin(x) from 0 to pi/2
    double a = 0.0, b = M_PI / 2;
    cout << "Integrating sin(x) from 0 to pi/2:\n";
    cout << "Trapezoidal: " << trapezoidal(f1, a, b, n) << endl;
    cout << "Simpson:     " << simpson(f1, a, b, n) << endl;
    cout << "Analytical:  1.0\n\n";

    // f2: x^3 from 0 to 1
    a = 0.0, b = 1.0;
    cout << "Integrating x^3 from 0 to 1:\n";
    cout << "Trapezoidal: " << trapezoidal(f2, a, b, n) << endl;
    cout << "Simpson:     " << simpson(f2, a, b, n) << endl;
    cout << "Analytical:  0.25\n\n";

    // f3: exp(-x^2) from 0 to 1
    cout << "Integrating exp(-x^2) from 0 to 1 (no exact analytical):\n";
    cout << "Trapezoidal: " << trapezoidal(f3, a, b, n) << endl;
    cout << "Simpson:     " << simpson(f3, a, b, n) << endl << endl;

    // f4: log(1 + x) from 0 to 1
    cout << "Integrating log(1 + x) from 0 to 1:\n";
    cout << "Trapezoidal: " << trapezoidal(f4, a, b, n) << endl;
    cout << "Simpson:     " << simpson(f4, a, b, n) << endl;
    cout << "Analytical:  0.38629436\n";
}

int main() {
    testIntegration();
    return 0;
}

/*Integrating sin(x) from 0 to pi/2:
Trapezoidal: 0.99999979
Simpson:     1.00000000
Analytical:  1.0

Integrating x^3 from 0 to 1:
Trapezoidal: 0.25000025
Simpson:     0.25000000
Analytical:  0.25

Integrating exp(-x^2) from 0 to 1 (no exact analytical):
Trapezoidal: 0.74682407
Simpson:     0.74682413

Integrating log(1 + x) from 0 to 1:
Trapezoidal: 0.38629432
Simpson:     0.38629436
Analytical:  0.38629436*/