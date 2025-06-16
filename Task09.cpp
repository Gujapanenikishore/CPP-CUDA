


/*Task 9: Vector Algebra Library (Individual)

Implement a templated vector algebra library supporting addition, scalar multiplication, dot and cross products, and normalization.

Include clear examples and test cases demonstrating correctness.*/


#include <iostream>
#include <cmath>
#include <cassert>
#include <iomanip>

using namespace std;

template <typename T>
class Vec3 {
public:
    T x, y, z;

    Vec3(T x = 0, T y = 0, T z = 0): x(x), y(y), z(z) {}

    // Vector addition
    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    // Scalar multiplication
    Vec3 operator*(T scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    // Dot product
    T dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vec3 cross(const Vec3& other) const {
        return Vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // Norm (length of vector)
    double norm() const {
        return sqrt(x*x + y*y + z*z);
    }

    // Normalized vector
    Vec3 normalize() const {
        double n = norm();
        if (n == 0) throw runtime_error("Cannot normalize zero vector");
        return Vec3(x / n, y / n, z / n);
    }

    // Output stream operator
    friend ostream& operator<<(ostream& os, const Vec3& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};

// Test cases
void testVectorLibrary() {
    cout << fixed << setprecision(4);

    Vec3<double> a(2.0, -1.0, 0.5);
    Vec3<double> b(-3.0, 4.0, 1.5);


    cout << "Vector A: " << a << endl;
    cout << "Vector B: " << b << endl;

    // Addition
    Vec3<double> sum = a + b;
    cout << "A + B = " << sum << endl;

    // Scalar multiplication
    Vec3<double> scaled = a * 2.0;
    cout << "A * 2 = " << scaled << endl;

    // Dot product
    double dot = a.dot(b);
    cout << "A . B = " << dot << endl;

    // Cross product
    Vec3<double> cross = a.cross(b);
    cout << "A x B = " << cross << endl;

    // Normalization
    Vec3<double> normA = a.normalize();
    cout << "Normalized A = " << normA << ", length = " << normA.norm() << endl;
}

int main() {
    testVectorLibrary();
    return 0;
}


/*____-
Sample Output

Vector A: (1.0000, 2.0000, 3.0000)
Vector B: (4.0000, 5.0000, 6.0000)
A + B = (5.0000, 7.0000, 9.0000)
A * 2 = (2.0000, 4.0000, 6.0000)
A . B = 32.0000
A x B = (-3.0000, 6.0000, -3.0000)
Normalized A = (0.2673, 0.5345, 0.8018), length = 1.0000*/
