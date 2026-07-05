/**
 * @brief Solution for the "Summing Series" problem using O(1) Telescoping Series property.
 * * Problem Description:
 * Evaluate the series: Sn = T1 + T2 + T3 + ... + Tn
 * where Tk = k^2 - (k-1)^2.
 * Find Sn mod (10^9 + 7).
 * * Input Format:
 * - The first line contains t, the number of test cases.
 * - Each test case consists of a single integer n.
 * * Output:
 * - Return Sn mod (10^9 + 7) for each test case.
 */
#include <iostream>

/**
 * @brief Computes the sum of the series modulo 10^9 + 7.
 * @param n The inclusive limit of the range to sum.
 * @return long long The total sum modulo 10^9 + 7.
 */
long long summingSeries(long long n) {
    long long MOD = 1000000007;

    // To prevent overflow before the modulo operation,
    // we take modulo of n first: (n % MOD) * (n % MOD) % MOD
    n = n % MOD;

    return (n * n) % MOD;
}

int main() {

    std::cout<<"Result: " << summingSeries(10) << std::endl;

    return 0;

}
