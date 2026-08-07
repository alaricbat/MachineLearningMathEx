#include "../include/PortfolioOptimizer.h"
#include "../include/KKTSolver.h"

#include "numeric"
#include <algorithm>

Portfolio PortfolioOptimizer::optimize(
        const std::vector<double>& expectedReturns,
        const std::vector<std::vector<double>>& covarianceMatrix) {
    Portfolio portfolio;
    portfolio.weights = solveQuadraticProgram(covarianceMatrix);
    if (!isFeasible(portfolio.weights)) {
        throw std::runtime_error("Portfolio optimization failed.");
    }
    portfolio.expectedReturn = portfolioReturn(
            portfolio.weights,
            expectedReturns);
    portfolio.expectedRisk = portfolioRisk(
            portfolio.weights,
            covarianceMatrix);
    return portfolio;
}

std::vector<double> PortfolioOptimizer::solveQuadraticProgram(const std::vector<std::vector<double>>& covarianceMatrix) {
    KKTSolver solver;
    return solver.solve(covarianceMatrix);
}


bool PortfolioOptimizer::isFeasible(const std::vector<double>& weights) {
    if (weights.empty()) return false;
    constexpr double EPSILON = 1e-8;
    double sum = std::accumulate(weights.begin(), weights.end(), 0.0);
    if (std::fabs(sum - 1.0) > EPSILON) {
        return false;
    }
    if (!std::all_of(weights.begin(), weights.end(), [EPSILON](double weight) {
        return weight >= -EPSILON;
    })) {
        return false;
    }
    return true;
}

double PortfolioOptimizer::portfolioRisk(
            const std::vector<double>& weights,
            const std::vector<std::vector<double>>& covarianceMatrix) {
    const size_t n = weights.size();

    if (n == 0) return 0.0;

    if (covarianceMatrix.size() != n)
        throw std::invalid_argument(
                "Covariance matrix dimension does not match weights.");

    double portfolioVariance = 0.0;

    for (size_t i = 0; i < n; ++i) {
        if (covarianceMatrix[i].size() != n)
            throw std::invalid_argument(
                    "Covariance matrix must be square.");
        for (size_t j = 0; j < n; ++j) {
            portfolioVariance +=
                    weights[i] * covarianceMatrix[i][j] * weights[j];
        }
    }

    return portfolioVariance;
}


double PortfolioOptimizer::portfolioReturn(
            const std::vector<double>& weights,
            const std::vector<double>& expectedReturns) {
    if (weights.size() != expectedReturns.size())
        throw std::invalid_argument(
                "Weights size must equal expected returns size.");
    double expectedPortfolioReturn = 0.0;
    for (size_t i = 0; i < weights.size(); ++i) {
        expectedPortfolioReturn += (weights[i] * expectedReturns[i]);
    }
    return expectedPortfolioReturn;
}

