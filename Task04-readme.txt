==============================================
TASK 4: EFFICIENT GENERIC CONCURRENT MERGE SORT
==============================================

OBJECTIVE:
----------
To implement a generic merge sort in C++ that:
- Supports any data type using templates
- Uses parallel execution with std::async
- Falls back to sequential sort for small ranges
- Benchmarks sequential vs parallel sort performance

--------------------------------------------------
DESIGN STRATEGY:
--------------------------------------------------

1. Uses classic Merge Sort algorithm (Divide and Conquer)
2. When the range is large, it splits the work into threads using async
3. When the range is small, it switches to sequential sort (adaptive threshold)
4. Measures time taken for both approaches using chrono

--------------------------------------------------
CONSTANT DEFINITION:
--------------------------------------------------

const size_t PARALLEL_THRESHOLD = 5000;

- This value decides when to switch from parallel to sequential sort
- If (right - left) <= threshold, use sequential
- If larger, split task using async

--------------------------------------------------
FUNCTIONS USED:
--------------------------------------------------

1. merge()
- Merges two sorted halves: [left, mid) and [mid, right)
- Uses temporary buffer and copy back logic

2. sequentialMergeSort()
- Traditional merge sort implementation
- Recursive division, sort, and merge

3. parallelMergeSort()
- Same structure as sequential
- But launches left half as an async task
- Right half runs on current thread
- Merges both after left finishes

4. runSequentialSort()
- Benchmarks time taken for sequential sort

5. runParallelSort()
- Benchmarks time taken for parallel sort

--------------------------------------------------
MAIN FUNCTION LOGIC:
--------------------------------------------------

1. Creates a vector of random integers
2. Fills with 200000 elements using uniform distribution
3. Calls both sequential and parallel sort runners
4. Prints time taken by each approach

--------------------------------------------------
COMPILATION AND RUNNING:
--------------------------------------------------

To compile:
  g++ -std=c++17 Task4.cpp -o mergesort -pthread

To run:
  ./mergesort

--------------------------------------------------
EXPECTED OUTPUT EXAMPLE:
--------------------------------------------------

Running with 200000 elements...
Sequential Sort Time: 90 ms
Parallel Sort Time: 50 ms

(Note: Times will vary depending on your system's CPU cores and load)

--------------------------------------------------
HOW TO CUSTOMIZE:
--------------------------------------------------

1. DATA SIZE:
   Change DATA_SIZE in main():
   const size_t DATA_SIZE = 500000;

2. PARALLEL THRESHOLD:
   Change PARALLEL_THRESHOLD:
   const size_t PARALLEL_THRESHOLD = 10000;

3. TYPE:
   Change vector<int> to vector<float> or vector<double> for generic testing

4. INPUT VALUES:
   Modify dist range in uniform_int_distribution for different number patterns

--------------------------------------------------
ADVANTAGES:
--------------------------------------------------

- Fully generic using template<T>
- Efficient use of system threads
- Adaptive threshold prevents overhead on small datasets
- Simple to scale by adjusting threshold

--------------------------------------------------
TOPICS COVERED:
--------------------------------------------------

- Merge sort algorithm
- std::async and parallel programming
- Adaptive execution threshold
- Template programming in C++
- High-resolution timing and benchmarking

