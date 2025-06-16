/*Task 1: Matrix Multiplication Class (Individual)

Implement a templated matrix class supporting efficient multiplication, addition, subtraction, and I/O operations.

Overload relevant operators (+, -, *, <<).

Clearly demonstrate correctness through comprehensive test cases, including edge cases.*/


#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std ;

// Templated Matrix class
template<typename T>
class Matrix {
private:
    vector<vector<T>> data;
    size_t rows, cols;

public:
    Matrix(size_t r, size_t c, T initial = T()) : rows(r), cols(c) {
        data.assign(r, vector<T>(c, initial));
    }

    Matrix(const vector<vector<T>>& values) {
        if (values.empty() || values[0].empty())
            throw invalid_argument("Matrix cannot be empty");
        rows = values.size();
        cols = values[0].size();
        data = values;
    }

    size_t rowCount() const { return rows; }
    size_t colCount() const { return cols; }

    vector<T>& operator[](size_t i) { return data[i]; }
    const vector<T>& operator[](size_t i) const { return data[i]; }

    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Dimension mismatch for addition");
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result[i][j] = data[i][j] + other[i][j];
        return result;
    }

    Matrix<T> operator-(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Dimension mismatch for subtraction");
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result[i][j] = data[i][j] - other[i][j];
        return result;
    }

    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.rows)
            throw invalid_argument("Invalid dimensions for multiplication");
        Matrix<T> result(rows, other.cols, T());
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < other.cols; ++j)
                for (size_t k = 0; k < cols; ++k)
                    result[i][j] += data[i][k] * other[k][j];
        return result;
    }

    friend ostream& operator<<(ostream& os, const Matrix<T>& m) {
        for (size_t i = 0; i < m.rows; ++i) {
            for (size_t j = 0; j < m.cols; ++j) {
                os << m[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }
};

// Main function with test cases
int main() {
    try {
        //  CHANGE HERE: Matrix A (you can modify the values)
        Matrix<int> A({{2, 4}, {6, 8}}); 

        //  CHANGE HERE: Matrix B (change to show different results)
        Matrix<int> B({{1, 3}, {5, 7}}); 

        cout << "Matrix A:\n" << A;
        cout << "Matrix B:\n" << B;

        //  You can comment/uncomment operations below for testing
        Matrix<int> C = A + B;
        cout << "\nA + B:\n" << C;

        Matrix<int> D = A - B;
        cout << "\nA - B:\n" << D;

        Matrix<int> E = A * B;
        cout << "\nA * B:\n" << E;

        //  CHANGE HERE: Float Matrix demo
        Matrix<float> F({{1.6, 2.2}, {3.3, 2.5}});
        Matrix<float> G({{2.4, 0.1}, {1.8, 1.5}});
        cout << "\nFloat Matrix F * G:\n" << (F * G);

        //  CHANGE HERE: Trigger error for mismatched sizes (comment out if not needed)
        // Matrix<int> X({{1, 2, 3}});
        // Matrix<int> errorTest = A + X; // Uncomment to test dimension error

    } catch (const exception& e) {
        cerr << "\nError: " << e.what() << endl;
    }

    return 0;
}


/*________________

OUTPUT


Matrix A:
1 2 
3 4 
Matrix B:
5 6 
7 8 

A + B:
6 8 
10 12 

A - B:
-4 -4 
-4 -4 

A * B:
19 22 
43 50 

Float Matrix F * G:
5 5.75 
10.5 12.75*/
