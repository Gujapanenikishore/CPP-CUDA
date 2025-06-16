=========================================
TASK 9: VECTOR ALGEBRA LIBRARY (C++)
=========================================

OBJECTIVE:
----------
To implement a generic (templated) 3D vector library that supports:

- Vector addition (A + B)
- Scalar multiplication (A * scalar)
- Dot product (A . B)
- Cross product (A x B)
- Normalization (unit vector)
- Operator overloading for stream output (<<)

----------------------------------------------------
CLASS TEMPLATE: Vec3<T>
----------------------------------------------------

TEMPLATED TYPE:
---------------
- Supports any numeric type (e.g., int, float, double)
- Common usage: Vec3<double>, Vec3<float>

DATA MEMBERS:
-------------
- T x, y, z — represent the 3D vector components

CONSTRUCTOR:
------------
Vec3(T x = 0, T y = 0, T z = 0)
- Default constructor sets all components to zero
- Custom constructor initializes with given values

----------------------------------------------------
OVERLOADED OPERATORS AND METHODS:
----------------------------------------------------

1. operator+ (Vector Addition):
   - Returns: new Vec3(x1 + x2, y1 + y2, z1 + z2)

2. operator* (Scalar Multiplication):
   - Multiplies each component by scalar

3. dot(const Vec3& other):
   - Returns scalar dot product:
     x1*x2 + y1*y2 + z1*z2

4. cross(const Vec3& other):
   - Returns vector cross product:
     A x B = (y1*z2 - z1*y2, z1*x2 - x1*z2, x1*y2 - y1*x2)

5. norm():
   - Returns the Euclidean norm (magnitude):
     √(x² + y² + z²)

6. normalize():
   - Returns a new Vec3 with unit length
   - Formula: A / ||A||
   - Throws runtime_error if zero vector is used

7. operator<< (Output):
   - Allows printing with cout
   - Format: (x, y, z)

----------------------------------------------------
TEST FUNCTION: testVectorLibrary()
----------------------------------------------------

Creates two 3D vectors:
- A = (2.0, -1.0, 0.5)
- B = (-3.0, 4.0, 1.5)

Then demonstrates the following:

1. Addition:
   A + B = (-1.0, 3.0, 2.0)

2. Scalar Multiplication:
   A * 2 = (4.0, -2.0, 1.0)

3. Dot Product:
   A . B = (2)*(-3) + (-1)*(4) + (0.5)*(1.5) = -6 - 4 + 0.75 = -9.25

4. Cross Product:
   A x B = determinant of 3x3 matrix
         = ((-1)*1.5 - 0.5*4, 0.5*(-3) - 2*1.5, 2*4 - (-1)*(-3))
         = (-1.5 - 2.0, -1.5 - 3.0, 8 - 3)
         = (-3.5, -4.5, 5.0)

5. Normalization:
   Norm of A = sqrt(2² + (-1)² + 0.5²) = sqrt(4 + 1 + 0.25) = sqrt(5.25) ≈ 2.291
   Normalized A = (2 / 2.291, -1 / 2.291, 0.5 / 2.291)
                ≈ (0.8738, -0.4369, 0.2184)

   Length of normalized A = 1

----------------------------------------------------
SAMPLE OUTPUT:
----------------------------------------------------

Vector A: (2.0000, -1.0000, 0.5000)
Vector B: (-3.0000, 4.0000, 1.5000)
A + B = (-1.0000, 3.0000, 2.0000)
A * 2 = (4.0000, -2.0000, 1.0000)
A . B = -9.2500
A x B = (-3.5000, -4.5000, 5.0000)
Normalized A = (0.8738, -0.4369, 0.2184), length = 1.0000

----------------------------------------------------
COMPILATION AND RUNNING:
----------------------------------------------------

To compile:
  g++ -std=c++17 Task9.cpp -o vector_math

To run:
  ./vector_math

----------------------------------------------------
MODIFICATIONS:
----------------------------------------------------

- Change values of A and B to test different cases
- Try with Vec3<float> or Vec3<int> types
- Try zero vector to see error in normalize()
- Add new operations like projection or angle between vectors

----------------------------------------------------
TOPICS COVERED:
----------------------------------------------------

- Template classes
- Operator overloading
- Vector algebra in 3D
- Dot and cross product math
- Exception handling (normalize)
- I/O formatting with iomanip

