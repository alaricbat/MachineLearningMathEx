#pragma once

#include "vector"

/**
 * @brief Solve a linear system Ax = b using Gaussian Elimination.
 *
 * Input:
 *      A : coefficient matrix (n x n)
 *      b : right-hand-side vector (n)
 *
 * Output:
 *      x : solution vector
 */
class LinearSolver {
public:

    /**
     * Solve Ax = b using Gaussian Elimination.
     */
    std::vector<double> solve(
            const std::vector<std::vector<double>>& A,
            const std::vector<double>& b);

private:

    /**
     * Convert matrix A to upper triangular matrix.
     */
    void forwardElimination(
            std::vector<std::vector<double>>& A,
            std::vector<double>& b);

    /**
     * Solve the upper triangular system.
     */
    std::vector<double> backwardSubstitution(
            const std::vector<std::vector<double>>& A,
            const std::vector<double>& b);
};