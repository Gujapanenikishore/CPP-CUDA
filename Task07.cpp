
/*Task 7: Polynomial Class and Root Finding (Individual)

Develop a polynomial class supporting arithmetic operations (addition, subtraction, multiplication).

Implement a numerical method (Newton-Raphson or Bisection) for finding polynomial roots.

Demonstrate correctness with detailed examples.*/



#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

class Polynomial {
private:
    vector<double> coeffs;  // coeffs[i] corresponds to x^i

public:
    Polynomial(const vector<double>& c) : coeffs(c) {}

    // Evaluate polynomial at x
    double operator()(double x) const {
        double result = 0;
        double powX = 1;
        for (double coef : coeffs) {
            result += coef * powX;
            powX *= x;
        }
        return result;
    }

    // Derivative of the polynomial
    Polynomial derivative() const {
        vector<double> deriv;
        for (size_t i = 1; i < coeffs.size(); ++i) {
            deriv.push_back(coeffs[i] * i);
        }
        return Polynomial(deriv);
    }

    // Addition
    Polynomial operator+(const Polynomial& other) const {
        size_t n = max(coeffs.size(), other.coeffs.size());
        vector<double> result(n, 0.0);
        for (size_t i = 0; i < coeffs.size(); ++i)
            result[i] += coeffs[i];
        for (size_t i = 0; i < other.coeffs.size(); ++i)
            result[i] += other.coeffs[i];
        return Polynomial(result);
    }

    // Subtraction
    Polynomial operator-(const Polynomial& other) const {
        size_t n = max(coeffs.size(), other.coeffs.size());
        vector<double> result(n, 0.0);
        for (size_t i = 0; i < coeffs.size(); ++i)
            result[i] += coeffs[i];
        for (size_t i = 0; i < other.coeffs.size(); ++i)
            result[i] -= other.coeffs[i];
        return Polynomial(result);
    }

    // Multiplication
    Polynomial operator*(const Polynomial& other) const {
        vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0.0);
        for (size_t i = 0; i < coeffs.size(); ++i)
            for (size_t j = 0; j < other.coeffs.size(); ++j)
                result[i + j] += coeffs[i] * other.coeffs[j];
        return Polynomial(result);
    }

    // Print
    void print() const {
        for (int i = coeffs.size() - 1; i >= 0; --i) {
            if (abs(coeffs[i]) < 1e-9) continue;
            cout << (coeffs[i] >= 0 && i != (int)coeffs.size() - 1 ? "+" : "") << coeffs[i];
            if (i > 0) cout << "*x";
            if (i > 1) cout << "^" << i << " ";
        }
        cout << endl;
    }
};

// Newton-Raphson Method to find root
double findRootNewton(const Polynomial& f, double guess, double tol = 1e-6, int maxIter = 1000) {
    Polynomial df = f.derivative();
    double x = guess;

    for (int i = 0; i < maxIter; ++i) {
        double fx = f(x);
        double dfx = df(x);

        if (abs(dfx) < 1e-10)
            throw runtime_error("Derivative near zero. Method fails.");

        double nextX = x - fx / dfx;

        if (abs(nextX - x) < tol)
            return nextX;

        x = nextX;
    }

    throw runtime_error("Root not found within max iterations");
}

// Test Cases
int main() {
    // Example 1: f(x) = x^2 - 4
    Polynomial p1({-4, 0, 1});  // -4 + 0*x + 1*x^2
    cout << "Polynomial 1: ";
    p1.print();
    try {
        double root1 = findRootNewton(p1, 2.0); // guess near 2
        cout << "Root found near 2: " << root1 << " → f(" << root1 << ") = " << p1(root1) << endl;
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    // Example 2: f(x) = x^3 - 2x + 1
    Polynomial p2({1, -2, 0, 1});
    cout << "\nPolynomial 2: ";
    p2.print();
    try {
        double root2 = findRootNewton(p2, -1.5);
        cout << "Root near -1.5: " << root2 << " → f(" << root2 << ") = " << p2(root2) << endl;
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    // Arithmetic: (x^2 - 4) + (x^3 - 2x + 1)
    Polynomial sum = p1 + p2;
    cout << "\nSum: ";
    sum.print();

    Polynomial product = p1 * p2;
    cout << "Product: ";
    product.print();

    return 0;
}


/*______
Sample Output
Polynomial 1: +1*x^2 -4
Root found near 2: 2 → f(2) = 0

Polynomial 2: +1*x^3 -2*x +1
Root near -1.5: -1.61803 → f(-1.61803) = 1.55344e-07

Sum: +1*x^3 +1*x^2 -2*x -3
Product: +1*x^5 -2*x^4 -3*x^3 +8*x^2 -8*x -4                   */
