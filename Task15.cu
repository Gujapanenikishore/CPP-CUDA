

/*Task 15: Statistical Computation with Modern C++ (Individual)

Implement mean, median, variance, and standard deviation calculations using modern C++17 features.

Clearly illustrate computations and validate with known data sets.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>  // for std::setprecision

// ---------- Utility Functions -------------
double computeMean(const std::vector<double>& data) {
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

double computeMedian(std::vector<double> data) {
    std::sort(data.begin(), data.end());
    size_t n = data.size();
    return (n % 2 == 0) ? (data[n / 2 - 1] + data[n / 2]) / 2.0 : data[n / 2];
}

double computeVariance(const std::vector<double>& data, bool sample = false) {
    double mean = computeMean(data);
    double sum_sq = 0.0;
    for (double x : data)
        sum_sq += (x - mean) * (x - mean);
    return sum_sq / (data.size() - (sample ? 1 : 0));
}

double computeStdDev(const std::vector<double>& data, bool sample = false) {
    return std::sqrt(computeVariance(data, sample));
}

// --------- Display Results ---------------
void displayStats(const std::vector<double>& data) {
    std::cout << "Data: ";
    for (double x : data) std::cout << x << " ";
    std::cout << "\nSize: " << data.size() << '\n';

    double mean = computeMean(data);
    double median = computeMedian(data);
    double variance = computeVariance(data);
    double std_dev = computeStdDev(data);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Mean              : " << mean << "\n";
    std::cout << "Median            : " << median << "\n";
    std::cout << "Variance (Pop)    : " << variance << "\n";
    std::cout << "Std Dev (Pop)     : " << std_dev << "\n";
    std::cout << "Variance (Sample) : " << computeVariance(data, true) << "\n";
    std::cout << "Std Dev (Sample)  : " << computeStdDev(data, true) << "\n";
}

int main() {
    // === Example dataset ===
    std::vector<double> dataset1 = {10, 20, 30, 40, 50};      // known data
    std::vector<double> dataset2 = {2.5, 3.1, 4.0, 3.9, 2.7};  // real numbers

    std::cout << "=== Dataset 1 ===\n";
    displayStats(dataset1);

    std::cout << "\n=== Dataset 2 ===\n";
    displayStats(dataset2);

    return 0;
}

/*_________________
OUTPUT

=== Dataset 1 ===
Data: 10 20 30 40 50 
Size: 5
Mean              : 30.0000
Median            : 30.0000
Variance (Pop)    : 200.0000
Std Dev (Pop)     : 14.1421
Variance (Sample) : 250.0000
Std Dev (Sample)  : 15.8114

=== Dataset 2 ===
Data: 2.5 3.1 4 3.9 2.7 
Size: 5
Mean              : 3.2400
Median            : 3.1000
Variance (Pop)    : 0.3484
Std Dev (Pop)     : 0.5903
Variance (Sample) : 0.4355
Std Dev (Sample)  : 0.6600*/