#include "../include/KKTSolver.h"
#include "../include/LinearSolver.h"

std::vector<double> KKTSolver::solve(const std::vector<std::vector<double>>& covarianceMatrix) {
    if (covarianceMatrix.empty())
    {
        throw std::invalid_argument(
                "Covariance matrix cannot be empty.");
    }
    LinearSolver solver;

    const auto kktMatrix = buildKKTMatrix(covarianceMatrix);
    const auto rhs = buildRightHandSide(covarianceMatrix.size());

    auto solution = solver.solve(kktMatrix, rhs);

    // Remove λ
    solution.pop_back();

    return solution;
}

std::vector<std::vector<double>> KKTSolver::buildKKTMatrix(
            const std::vector<std::vector<double>>& covarianceMatrix) {
    const size_t n = covarianceMatrix.size();
    std::vector<std::vector<double>> kkt (
            n + 1,
            std::vector<double>(n + 1, 0.0)
            );
    // Copy Σ
    for (size_t row = 0; row < n; ++row) {
        for(size_t col = 0; col < n; ++col) {
            kkt[row][col] = covarianceMatrix[row][col];
        }
    }

    //Last column
    for (size_t row = 0; row < n; ++row) {
        kkt[row][n] = 1.0;
    }

    //Last row
    for (size_t col = 0; col < n; ++col) {
        kkt[n][col] = 1.0;
    }

    return kkt;
}

std::vector<double> KKTSolver::buildRightHandSide(size_t numberOfAssets) {
    std::vector<double> rhs(
            numberOfAssets + 1,
            0.0);
    rhs[numberOfAssets] = 1;
    return rhs;
}
