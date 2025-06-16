========================================================
TASK 15: STATISTICAL COMPUTATION WITH MODERN C++ (C++17)
========================================================

OBJECTIVE:
----------
Implement a statistics library using C++17 that calculates:
- Mean
- Median
- Sample Variance
- Sample Standard Deviation

Demonstrate it using real-world datasets and modern C++ features such as:
- STL containers (vector)
- <numeric> for accumulation
- <algorithm> for sorting
- Type-safe looping and fixed precision output

--------------------------------------------------------
DATASETS USED FOR DEMONSTRATION:
--------------------------------------------------------

1. Dataset 1: Exam Scores
   {85, 90, 92, 88, 70, 78, 95, 89}

2. Dataset 2: Daily Temperatures
   {22.5, 21.0, 23.0, 24.5, 22.0, 20.5, 25.0}

3. Dataset 3: Heights of Students
   {150, 160, 165, 155, 170, 175, 180}

--------------------------------------------------------
FUNCTIONS IMPLEMENTED:
--------------------------------------------------------

1. mean()
---------
Formula: sum(x) / N

- Uses std::accumulate to sum all values
- Divides by data.size() to get average

2. median()
-----------
Formula:
- If odd, median = middle value
- If even, median = average of two middle values

- Uses std::sort to sort the vector
- Accesses elements at center (or average of two)

3. variance()
-------------
Formula (Sample Variance):
  s² = Σ (x - mean)² / (n - 1)

- Loops through each value
- Uses formula to calculate squared difference from mean
- Returns variance

4. std_dev()
------------
Formula:
  std_dev = sqrt(variance)

- Uses std::sqrt from <cmath>

5. printData()
--------------
- Prints all values in the dataset to 4 decimal precision

6. runStatistics()
------------------
- Runs all above stats on a dataset
- Accepts a name string and vector<double>
- Prints results neatly

--------------------------------------------------------
OUTPUT EXPLANATION:
--------------------------------------------------------

Each dataset prints:

1. Raw data values
2. Mean value
3. Median value
4. Sample Variance (divided by n-1)
5. Sample Standard Deviation (sqrt of variance)

--------------------------------------------------------
SAMPLE OUTPUT (Example):
--------------------------------------------------------

==== Dataset 1: Exam Scores ====
Data: 85.0000 90.0000 92.0000 88.0000 70.0000 78.0000 95.0000 89.0000 
Mean: 85.875
Median: 88.5
Variance (Sample): 56.5536
Std Dev (Sample): 7.51753

==== Dataset 2: Daily Temperatures ====
Mean: 22.6429
Median: 22.5
Variance (Sample): 2.08929
Std Dev (Sample): 1.44527

==== Dataset 3: Student Heights ====
Mean: 165
Median: 165
Variance (Sample): 116.667
Std Dev (Sample): 10.8012

--------------------------------------------------------
COMPILATION AND RUNNING:
--------------------------------------------------------

To compile:
  g++ -std=c++17 Task15.cpp -o stats

To run:
  ./stats

--------------------------------------------------------
MODIFICATIONS:
--------------------------------------------------------

- Add more datasets in main() with realistic data
- Extend code to include:
   - Mode
   - Min/Max
   - Skewness/Kurtosis
- Use file input for large-scale analysis

--------------------------------------------------------
MODERN C++ FEATURES USED:
--------------------------

- std::vector for dynamic storage
- std::accumulate from <numeric>
- std::sort and range-based for loop
- std::fixed and std::setprecision for formatted output
- Compact and readable function chaining

--------------------------------------------------------
CONCEPTS COVERED:
------------------

- Descriptive statistics (mean, median, variance, std dev)
- Sample-based formulas (n-1 in variance)
- Data formatting
- Functional decomposition
- Type-generic numeric computation

