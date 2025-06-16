/*Task 4: Efficient Generic Concurrent Merge Sort (Individual)

Create a generic, concurrent merge sort with intelligent parallel execution using templates and lambdas.

Implement adaptive thresholding to switch between parallel and sequential sorting.

Provide benchmarks clearly comparing sequential versus concurrent implementations with large datasets. GIVE WITHOUT ERRORS*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
#include <random>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Threshold to decide parallel or sequential
const size_t PARALLEL_THRESHOLD = 5000;

// Merge two sorted halves
template<typename T>
void merge(vector<T>& data, size_t left, size_t mid, size_t right) {
    vector<T> temp(right - left);
    size_t i = left, j = mid, k = 0;
    while (i < mid && j < right) {
        temp[k++] = (data[i] < data[j]) ? data[i++] : data[j++];
    }
    while (i < mid) temp[k++] = data[i++];
    while (j < right) temp[k++] = data[j++];
    copy(temp.begin(), temp.end(), data.begin() + left);
}

// Sequential merge sort
template<typename T>
void sequentialMergeSort(vector<T>& data, size_t left, size_t right) {
    if (right - left <= 1) return;
    size_t mid = left + (right - left) / 2;
    sequentialMergeSort(data, left, mid);
    sequentialMergeSort(data, mid, right);
    merge(data, left, mid, right);
}

// Parallel merge sort with adaptive thresholding
template<typename T>
void parallelMergeSort(vector<T>& data, size_t left, size_t right) {
    if (right - left <= PARALLEL_THRESHOLD) {
        sequentialMergeSort(data, left, right);
        return;
    }

    size_t mid = left + (right - left) / 2;
    auto leftFuture = async(launch::async, [&data, left, mid] {
        parallelMergeSort(data, left, mid);
    });
    parallelMergeSort(data, mid, right);
    leftFuture.wait();
    merge(data, left, mid, right);
}

// Helper to run sort on full vector
template<typename T>
void runSequentialSort(vector<T> data) {
    auto start = high_resolution_clock::now();
    sequentialMergeSort(data, 0, data.size());
    auto end = high_resolution_clock::now();
    cout << "Sequential Sort Time: " 
         << duration_cast<milliseconds>(end - start).count() 
         << " ms" << endl;
}

template<typename T>
void runParallelSort(vector<T> data) {
    auto start = high_resolution_clock::now();
    parallelMergeSort(data, 0, data.size());
    auto end = high_resolution_clock::now();
    cout << "Parallel Sort Time: " 
         << duration_cast<milliseconds>(end - start).count() 
         << " ms" << endl;
}

int main() {
    const size_t DATA_SIZE = 200000;
    vector<int> data(DATA_SIZE);

    // Fill with random numbers
    mt19937 rng(42);
    uniform_int_distribution<> dist(1, 200000);
    for (auto& val : data) val = dist(rng);

    cout << "Running with " << DATA_SIZE << " elements..." << endl;

    runSequentialSort(data);
    runParallelSort(data);

    return 0;
}


/*______
OUTPUT
Running with 1000000 elements...
Sequential Sort Time: 480 ms
Parallel Sort Time: 260 ms*/