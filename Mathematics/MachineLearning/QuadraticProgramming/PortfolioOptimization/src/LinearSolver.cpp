#include "../include/LinearSolver.h"

std::vector<double> LinearSolver::solve(
            const std::vector<std::vector<double>>& A,
            const std::vector<double>& b) {
    std::vector<std::vector<double>> augmentedA = A;
    std::vector<double> augmentedB = b;
    forwardElimination(augmentedA, augmentedB);
    return backwardSubstitution(augmentedA, augmentedB);
}

void LinearSolver::forwardElimination(
            std::vector<std::vector<double>>& A,
            std::vector<double>& b) {
    const size_t n = A.size();
    for (size_t i = 0; i < n; ++i) {
        size_t maxRow = i;
        for (size_t k = i + 1; k < n; ++k) {
            if (std::abs(A[k][i]) > std::abs(A[maxRow][i])) {
                maxRow = k;
            }
        }

        if (maxRow != i) {
            std::swap(A[i], A[maxRow]);
            std::swap(b[i], b[maxRow]);
        }

        //Singular Matrix
        if (std::abs(A[i][i]) < 1e-9) {
          throw std::runtime_error("Matrix is singular or rank deficient!");
        }

        for (size_t k = i + 1; k < n; ++k) {
            double factor = A[k][i] / A[i][i];
            for (size_t j = i; j < n; ++j) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }
}

std::vector<double> LinearSolver::backwardSubstitution(
            const std::vector<std::vector<double>>& A,
            const std::vector<double>& b) {
    const size_t n = A.size();
    std::vector<double> x(n, 0.0);
    for (int i = static_cast<int>(n) - 1; i >= 0; --i) {
        double sum = 0.0;
        for (size_t j = i + 1; j < n; ++j) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }
    return x;
}

