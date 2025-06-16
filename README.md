=====================================================
C++ PROJECT README - Tasks 1 to 10 and Task 15
=====================================================

  
Language: Modern C++17  
Compiler: g++ (or compatible)

-----------------------------------------------------
SUMMARY
-----------------------------------------------------
This repository contains C++ implementations of 11 tasks that demonstrate core programming concepts such as matrix operations, statistical analysis, expression parsing, threading, numerical methods, and Monte Carlo simulation. Code is written using modern C++17 features with clear structure and test cases.

Tasks Included:
- Task 01: Matrix Multiplication Class
- Task 02: Arithmetic Expression Evaluator
- Task 03: Advanced Thread Pool
- Task 04: Concurrent Merge Sort
- Task 05: Lock-Free Smart Pointer
- Task 06: Multi-Queue Producer-Consumer
- Task 07: Polynomial Root Finding
- Task 08: Numerical Integration
- Task 09: Vector Algebra Library
- Task 10: Monte Carlo Pi Estimation
- Task 15: Statistical Computation Library

-----------------------------------------------------
TASK 1: MATRIX MULTIPLICATION CLASS
-----------------------------------------------------
- Implements a generic matrix class using templates
- Supports +, -, *, and << operators
- Includes dimension mismatch validation

-----------------------------------------------------
TASK 2: EXPRESSION EVALUATOR
-----------------------------------------------------
- Evaluates mathematical expressions with:
  +, -, *, / and parentheses
- Uses stack-based parsing
- Handles precedence and associativity

-----------------------------------------------------
TASK 3: ADVANCED THREAD POOL
-----------------------------------------------------
- Thread pool with:
  - Task prioritization
  - Dependency handling (via futures)
  - Exception propagation
- Built using std::thread and std::condition_variable

-----------------------------------------------------
TASK 4: PARALLEL MERGE SORT
-----------------------------------------------------
- Generic merge sort with:
  - Sequential and multithreaded versions
  - Adaptive threshold switching
- Uses std::async and lambda functions

-----------------------------------------------------
TASK 5: LOCK-FREE SMART POINTER
-----------------------------------------------------
- Custom smart pointer using atomic reference counting
- No mutex or locks used
- Compared with std::shared_ptr under stress tests

-----------------------------------------------------
TASK 6: MULTI-QUEUE PRODUCER-CONSUMER
-----------------------------------------------------
- Multi-threaded producer-consumer design
- Each consumer can steal tasks from others
- Uses mutex and condition_variable for sync

-----------------------------------------------------
TASK 7: POLYNOMIAL CLASS AND ROOT FINDING
-----------------------------------------------------
- Polynomial arithmetic: +, -, *, and evaluation
- Newton-Raphson method for root approximation
- Robust error checking for convergence

-----------------------------------------------------
TASK 8: NUMERICAL INTEGRATION
-----------------------------------------------------
- Supports:
  - Trapezoidal Rule
  - Simpson’s Rule (with even number of intervals)
- Compares numerical results against known analytical integrals

-----------------------------------------------------
TASK 9: VECTOR ALGEBRA LIBRARY
-----------------------------------------------------
- 3D Vector class with:
  - Addition
  - Scalar multiplication
  - Dot and Cross product
  - Norm and normalization

-----------------------------------------------------
TASK 10: MONTE CARLO PI ESTIMATION
-----------------------------------------------------
- Estimates value of π using Monte Carlo simulation
- Generates random (x, y) points in unit square
- Compares points inside a unit circle vs total points
- Accuracy improves with sample size

Sample Sizes Used: 100, 1,000, 10,000, 100,000, 1,000,000  
Outputs error value for each sample size

-----------------------------------------------------
TASK 15: STATISTICAL COMPUTATION
-----------------------------------------------------
- Computes:
  - Mean
  - Median
  - Sample Variance
  - Sample Standard Deviation
- Uses std::accumulate, sort, and vector datasets

-----------------------------------------------------
BUILD INSTRUCTIONS
-----------------------------------------------------
To compile each C++ task (example Task1.cpp):
  g++ -std=c++17 Task1.cpp -o task1
  ./task1

For multithreaded tasks (e.g., Task3, Task6):
  g++ -std=c++17 Task3.cpp -o task3 -pthread

-----------------------------------------------------
NOTES
-----------------------------------------------------
- All tasks are written in clean, testable C++17
- Each task includes hardcoded test cases and output
- Console output formatted for clarity

-----------------------------------------------------
CREDITS
-----------------------------------------------------
Developed as part of an advanced C++ project series.  
CUDA-based tasks (11–14) are documented separately.  
This README covers C++ tasks only.


