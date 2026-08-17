#include "../include/MatrixSolver.h"

#include "vector"

std::vector<std::vector<double>> MatrixSolver::transpose(const std::vector<std::vector<double>>& A) {
    if (A.empty() || A[0].empty()) return {};

    const size_t rows = A.size();
    const size_t cols = A[0].size();

    std::vector<std::vector<double>> A_T(cols, std::vector<double>(rows, 0.0));

    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            A_T[col][row] = A[row][col];
        }
    }
    return A_T;
}