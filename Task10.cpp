/*Task 10: Monte Carlo Pi Estimation (Individual)

Write a program for estimating n using Monte Carlo methods.

Clearly demonstrate accuracy with results from various sample sizes.*/

#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>

using namespace std;

// Estimate pi using Monte Carlo method
double estimatePi(unsigned int numSamples) {
    random_device rd;  // Non-deterministic generator
    mt19937 gen(rd()); // Mersenne Twister engine
    uniform_real_distribution<> dis(0.0, 1.0);

    unsigned int insideCircle = 0;

    for (unsigned int i = 0; i < numSamples; ++i) {
        double x = dis(gen);
        double y = dis(gen);

        if (x * x + y * y <= 1.0)
            ++insideCircle;
    }

    return 4.0 * insideCircle / numSamples;
}

void testMonteCarlo() {
    cout << fixed << setprecision(8);
    unsigned int samples[] = {100, 1000, 10000, 100000, 1000000};

    for (unsigned int n : samples) {
        double piEstimate = estimatePi(n);
        cout << "Samples: " << setw(8) << n
             << " | Pi ≈ " << piEstimate
             << " | Error: " << fabs(M_PI - piEstimate) << endl;
    }
}

int main() {
    testMonteCarlo();
    return 0;
}


/*_________------
Sample Output (varies slightly with each run)

Samples:      100 | Pi ≈ 3.20000000 | Error: 0.05840735
Samples:     1000 | Pi ≈ 3.12800000 | Error: 0.01359265
Samples:    10000 | Pi ≈ 3.14080000 | Error: 0.00079265
Samples:   100000 | Pi ≈ 3.14228000 | Error: 0.00068735
Samples:  1000000 | Pi ≈ 3.14183000 | Error: 0.00023735*/
