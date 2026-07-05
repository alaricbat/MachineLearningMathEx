/**
 * @brief Solution for the "Moving Tiles" problem using Relative Velocity and Geometry.
 * * Problem Description:
 * Two squares of side length 'l' are initially placed completely overlapping each other
 * at the origin. They both start moving along the diagonal line (y = x) at 45 degrees
 * with constant velocities 's1' and 's2' respectively. As they drift apart, the
 * overlapping area decreases. For each query 'q' representing a target overlapping
 * area, find the exact time 't' when the overlap area becomes equal to 'q'.
 * * Mathematical Formula Derived:
 * t = (sqrt(2) * (l - sqrt(q))) / |s1 - s2|
 * * Constraints & Accuracy:
 * - Output must be within 0.0001 of the true scale.
 * - Time Complexity per query: O(1).
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/**
 * @brief Solves the Moving Tiles queries.
 * @param l Side length of the two squares.
 * @param s1 Velocity of the first square.
 * @param s2 Velocity of the second square.
 * @param queries A vector containing the target overlapping areas.
 * @return vector<double> An array of times corresponding to each query.
 */
vector<double> movingTiles(int l, int s1, int s2, vector<int> queries) {
    vector<double> answers;
    answers.reserve(queries.size());
    double relativeVelocity = abs(s1 - s2);

    for (int q : queries) {
        if ((double)q == l * l) {
            answers.push_back(0.0);
            continue;
        }
        if (relativeVelocity == 0) {
            answers.push_back(0.0);
            continue;
        }
        double sqrtQ = sqrt(q);
        double result = (sqrt(2) * (l - sqrtQ)) / relativeVelocity;
        answers.push_back(result);
    }
    return answers;
}

int main() {
    vector<int> queries;
    queries.push_back(50);
    queries.push_back(100);
    vector<double> results = movingTiles(10, 1, 2, queries);
    for (double result : results) {
        cout << "Result = " << result << endl;
    }
    return 0;
}