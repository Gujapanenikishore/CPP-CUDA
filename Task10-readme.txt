==========================================
TASK 10: MONTE CARLO PI ESTIMATION (C++)
==========================================

OBJECTIVE:
----------
Estimate the value of Pi (π) using a statistical Monte Carlo method:
- Randomly generate points inside a square
- Count how many fall within the quarter circle
- Use probability ratio to estimate Pi

------------------------------------------
CONCEPT: MONTE CARLO METHOD FOR π
------------------------------------------

1. Consider a unit square with side = 1 (x in [0, 1], y in [0, 1])
2. Inside it, inscribe a quarter-circle of radius = 1 (centered at origin)
   Circle equation: x^2 + y^2 <= 1
3. Area of full circle = πr² = π(1)² = π
   Area of quarter circle = π / 4
4. Probability that a random point (x, y) lies inside the quarter-circle = π / 4
5. So, if N points are randomly generated:
   - Let K be the number of points inside the circle
   - Then: K / N ≈ π / 4  =>  π ≈ 4 * K / N

------------------------------------------
FUNCTION: estimatePi()
-----------------------
Input: number of random samples
Logic:
- Generate N random points in [0,1] x [0,1]
- Count how many fall within x^2 + y^2 <= 1
- Return 4.0 * inside / total

Tools:
- random_device + mt19937: for high-quality random number generation
- uniform_real_distribution: for generating x, y in [0, 1]

------------------------------------------
FUNCTION: testMonteCarlo()
---------------------------
- Runs the estimator for different sample sizes:
  {100, 1000, 10000, 100000, 1000000}
- For each, prints:
  - Estimated Pi
  - Absolute error from true value (M_PI)

------------------------------------------
OUTPUT FORMAT:
---------------
Samples:      N | Pi ≈ value | Error: difference_from_M_PI

Example:
Samples:     1000 | Pi ≈ 3.12800000 | Error: 0.01359265

(Note: Output varies slightly with each run due to randomness)

------------------------------------------
EXPECTED OUTPUT (EXAMPLE):
---------------------------
Samples:      100 | Pi ≈ 3.20000000 | Error: 0.05840735
Samples:     1000 | Pi ≈ 3.12800000 | Error: 0.01359265
Samples:    10000 | Pi ≈ 3.14080000 | Error: 0.00079265
Samples:   100000 | Pi ≈ 3.14228000 | Error: 0.00068735
Samples:  1000000 | Pi ≈ 3.14183000 | Error: 0.00023735

Observation:
- As sample size increases, accuracy improves
- Converges slowly but steadily towards π

------------------------------------------
COMPILATION AND RUNNING:
-------------------------

To compile:
  g++ -std=c++17 Task10.cpp -o montecarlo -lm

To run:
  ./montecarlo

------------------------------------------
MODIFICATION OPTIONS:
----------------------

- Add timing code to measure speed (chrono)
- Try higher sample counts (10 million+)
- Use threads for parallel estimation
- Store estimates in a file or graph results

------------------------------------------
CONCEPTS DEMONSTRATED:
-----------------------

- Random number generation
- Geometry: circle and square area
- Probability-based approximation
- Convergence of estimators
- Accuracy/error analysis
- Precision formatting (iomanip)
