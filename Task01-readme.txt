=======================================
TASK 1: MATRIX MULTIPLICATION CLASS (C++)
=======================================

OBJECTIVE:
----------
Implement a C++ class template for a Matrix that supports:

- Matrix Addition (+)
- Matrix Subtraction (-)
- Matrix Multiplication (*)
- Matrix Printing (<< operator)
- Type-generic (int, float, double, etc.)
- Handles edge cases like dimension mismatches with exceptions

-----------------------------------
IMPLEMENTATION OVERVIEW:
-----------------------------------

Class: Matrix<T>
A template class that allows creating a matrix of any data type T.

Internal Storage:
Uses a 2D vector:
  vector<vector<T>> data;
Each inner vector represents a row of the matrix.

Constructors:
- Matrix(rows, cols, initial_val)
  Creates a matrix of given size, initializing all elements to 'initial_val'.

- Matrix(nested_vector)
  Initializes matrix directly using a 2D vector (e.g., {{1, 2}, {3, 4}})

----------------------------------
OPERATOR OVERLOADING LOGIC:
----------------------------------

1. Addition Operator (A + B)
- Preconditions: Same dimensions
- Logic: element-wise addition
  result[i][j] = A[i][j] + B[i][j]

2. Subtraction Operator (A - B)
- Preconditions: Same dimensions
- Logic: element-wise subtraction
  result[i][j] = A[i][j] - B[i][j]

3. Multiplication Operator (A * B)
- Preconditions: A.cols == B.rows
- Logic: standard matrix multiplication
  result[i][j] = sum(A[i][k] * B[k][j]) for all k

4. Output Operator (<<)
- Overloaded to allow using cout << matrix;
- Prints each element in matrix row-wise

5. Error Handling:
- Throws std::invalid_argument("Dimension mismatch") 
  if the matrix sizes are incompatible for the operation

--------------------------------------
FUNCTION DESIGN DETAILS:
--------------------------------------

- rowCount() / colCount(): Return matrix size
- operator[](i): Access row i
- Templated for use with int, float, double, etc.
- Uses const correctness for read-only functions
- Exception-safe with try-catch block in main()

------------------------------------------
MAIN FUNCTION: TEST CASES AND EXPECTED OUTPUT
------------------------------------------

Matrix A = {{2, 4}, {6, 8}}
Matrix B = {{1, 3}, {5, 7}}

1. A + B:
   => {{3, 7}, {11, 15}}

2. A - B:
   => {{1, 1}, {1, 1}}

3. A * B:
   => Multiply using standard matrix multiplication logic
   => {{22, 34}, {46, 74}}

4. Float Matrix Multiplication:
   Matrix<float> F = {{1.6, 2.2}, {3.3, 2.5}}
   Matrix<float> G = {{2.4, 0.1}, {1.8, 1.5}}

   Output will be the product of F * G as float values

5. Error Case:
   Matrix X = {{1, 2, 3}} (1x3)
   A + X will throw a dimension mismatch error

-------------------------------------
HOW TO COMPILE AND RUN:
-------------------------------------

Compile:
  g++ -std=c++17 Task1.cpp -o matrix

Run:
  ./matrix

-------------------------------------
HOW TO MODIFY TEST CASES:
-------------------------------------

- Change values of A and B to use different integers
- Use float or double by changing Matrix<int> to Matrix<float>
- Add more rows or columns to test dynamic sizing
- Uncomment the dimension mismatch test to verify error handling

-------------------------------------
SUMMARY OF CONCEPTS IMPLEMENTED:
-------------------------------------

- Templated Class in C++
- Operator Overloading: +, -, *, <<
- Matrix Operations (Addition, Subtraction, Multiplication)
- Nested Vector (2D data structure)
- Exception Handling using std::invalid_argument
- Clean and testable main() function

