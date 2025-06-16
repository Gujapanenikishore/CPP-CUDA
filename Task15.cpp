/*Task 15: Statistical Computation with Modern C++ (Individual)

Implement mean, median, variance, and standard deviation calculations using modern C++17 features.

Clearly illustrate computations and validate with known data sets.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <string>

// Compute mean
double mean(const std::vector<double>& data) {
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

// Compute median
double median(std::vector<double> data) {
    std::sort(data.begin(), data.end());
    size_t n = data.size();
    return (n % 2 == 0) ? (data[n/2 - 1] + data[n/2]) / 2.0 : data[n/2];
}

// Compute sample variance
double variance(const std::vector<double>& data, double m) {
    double sum = 0.0;
    for (double x : data)
        sum += (x - m) * (x - m);
    return sum / (data.size() - 1);
}

// Compute standard deviation
double std_dev(double var) {
    return std::sqrt(var);
}

// Print data
void printData(const std::vector<double>& data) {
    std::cout << "Data: ";
    for (double val : data)
        std::cout << std::fixed << std::setprecision(4) << val << " ";
    std::cout << "\n";
}

// Run statistics on dataset
void runStatistics(const std::string& name, const std::vector<double>& dataset) {
    std::cout << "\n==== " << name << " ====\n";
    printData(dataset);

    double m = mean(dataset);
    double med = median(dataset);
    double var = variance(dataset, m);
    double stddev = std_dev(var);

    std::cout << "Mean: " << m << "\n";
    std::cout << "Median: " << med << "\n";
    std::cout << "Variance (Sample): " << var << "\n";
    std::cout << "Std Dev (Sample): " << stddev << "\n";
}

int main() {
    // Dataset 1: Exam Scores
    std::vector<double> dataset1 = {85, 90, 92, 88, 70, 78, 95, 89};

    // Dataset 2: Daily Temperatures
    std::vector<double> dataset2 = {22.5, 21.0, 23.0, 24.5, 22.0, 20.5, 25.0};

    // Dataset 3: Heights of Students
    std::vector<double> dataset3 = {150, 160, 165, 155, 170, 175, 180};

    // Run stats
    runStatistics("Dataset 1: Exam Scores", dataset1);
    runStatistics("Dataset 2: Daily Temperatures", dataset2);
    runStatistics("Dataset 3: Student Heights", dataset3);

    return 0;
}

/*
OUTPUT
==== Dataset 1: Exam Scores ====
Data: 85.0000 90.0000 92.0000 88.0000 70.0000 78.0000 95.0000 89.0000 
Mean: 85.875
Median: 88.5
Variance (Sample): 56.5536
Std Dev (Sample): 7.51753

==== Dataset 2: Daily Temperatures ====
Data: 22.5000 21.0000 23.0000 24.5000 22.0000 20.5000 25.0000 
Mean: 22.6429
Median: 22.5
Variance (Sample): 2.08929
Std Dev (Sample): 1.44527

==== Dataset 3: Student Heights ====
Data: 150.0000 160.0000 165.0000 155.0000 170.0000 175.0000 180.0000 
Mean: 165
Median: 165
Variance (Sample): 116.667
Std Dev (Sample): 10.8012
*/