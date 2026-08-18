#include "../include/KKTSolver.h"
#include "../include/LinearSolver.h"
#include "../include/MatrixSolver.h"

std::vector<double> KKTSolver::solve(
        const std::vector<std::vector<double>>& covarianceMatrix,
        const std::vector<std::vector<double>>& activeMatrix,
        const std::vector<double>& xVector,
        const std::vector<double>& cVector) {
    if (covarianceMatrix.empty())
    {
        throw std::invalid_argument(
                "Covariance matrix cannot be empty.");
    }
    LinearSolver solver;

    const auto kktMatrix = buildKKTMatrix(covarianceMatrix, activeMatrix);
    const auto rhs = buildRightHandSide(covarianceMatrix, activeMatrix, xVector, cVector);

    auto solution = solver.solve(kktMatrix, rhs);

    return solution;
}

std::vector<std::vector<double>> KKTSolver::buildKKTMatrix(
            const std::vector<std::vector<double>>& covarianceMatrix,
             const std::vector<std::vector<double>>& activeMatrix) {
    const size_t co_n = covarianceMatrix.size();
    const size_t ac_n = activeMatrix.size();
    const size_t n = co_n + ac_n;
    std::vector<std::vector<double>> kkt (
            n,
            std::vector<double>(n, 0.0)
            );

    // [ Σ  Aᵀ]
    // [A  0 ]

    // Copy Σ
    for (size_t row = 0; row < co_n; ++row) {
        for(size_t col = 0; col < co_n; ++col) {
            kkt[row][col] = covarianceMatrix[row][col];
        }
    }

    // Copy A
    for (size_t row = 0; row < ac_n; ++row) {
        for (size_t col = 0; col < co_n; ++col) {
            kkt[co_n + row][col] = activeMatrix[row][col];
        }
    }

    MatrixSolver matrixSolver;

    // Copy A.T
    std::vector<std::vector<double>> activeMatrixTranspose = matrixSolver.transpose(activeMatrix);
    for (size_t row = 0; row < co_n; ++row) {
        for (size_t col = 0; col < ac_n; ++ col) {
            kkt[row][co_n + col] = activeMatrixTranspose[row][col];
        }
    }

    return kkt;
}

std::vector<double> KKTSolver::buildRightHandSide(
        const std::vector<std::vector<double>>& covarianceMatrix,
        const std::vector<std::vector<double>>& activeMatrix,
        const std::vector<double>& xVector,
        const std::vector<double>& cVector) {
    bool isCEmpty = false;
    if (cVector.empty()) isCEmpty = true;
    if (covarianceMatrix.size() != xVector.size()) {
        throw std::invalid_argument(
                "Q Matrix did not map size with V Vector.");
    }
    const size_t numOfContraints = activeMatrix.size();
    const size_t n = covarianceMatrix.size() + numOfContraints;
    std::vector<double> rhs(n, 0.0);
    std::vector<double> gVector(covarianceMatrix.size(), 0.0);
    for (size_t row = 0; row < covarianceMatrix.size(); ++row) {
        double result = 0.0;
        for (size_t col = 0; col < covarianceMatrix.size(); ++col) {
            result += covarianceMatrix[row][col] * xVector[col];
        }
        if (!isCEmpty) result += cVector[row];
        gVector[row] = (-1) * result;
    }
    // Adding g vector.
    for (size_t i = 0; i < gVector.size(); ++i) {
        rhs[i] = gVector[i];
    }
    return rhs;
}
