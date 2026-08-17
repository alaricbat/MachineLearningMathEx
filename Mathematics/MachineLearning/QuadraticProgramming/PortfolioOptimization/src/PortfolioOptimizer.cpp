#include "../include/PortfolioOptimizer.h"
#include "../include/ReturnCalculator.h"
#include "../include/ActiveSetSolver.h"
#include "../include/CovarianceMatrix.h"

#include "numeric"
#include <algorithm>

Portfolio PortfolioOptimizer::optimize(const std::vector<StockData>& stocks) {

    ReturnCalculator calculator;
    CovarianceMatrix coMatrix;
    Portfolio portfolio;

    std::map<std::string, std::vector<double>> calResult = calculator.calculate(stocks);

    // Identify the covariance matrix
    std::vector<std::vector<double>> covarianceMatrix = coMatrix.calculate(calResult);

    // Identify the active matrix
    std::vector<std::vector<double>> activeMatrix(
            calResult.size() + 1,
            std::vector<double>(calResult.size())
            );
    // Set up the value of active matrix (A)
    for (double & col : activeMatrix[0]) {
        col = 1;
    }
    int minusCol = 0;
    for (size_t row = 1; row < activeMatrix.size(); ++row) {
        activeMatrix[row][minusCol] = -1;
        minusCol++;
    }
    // Set up b vector
    std::vector<double> bVector(calResult.size() + 1, 0.0);
    bVector[0] = 1;

    //Initial the vector of weights
    //Important step !
    std::vector<double> weight(covarianceMatrix.size(), 1.0);

    portfolio.weights = solveQuadraticProgram(
            covarianceMatrix,
            activeMatrix,
            bVector,
            weight,
            {});
    if (!isFeasible(portfolio.weights)) {
        throw std::runtime_error("Portfolio optimization failed.");
    }

    std::vector<std::string> tickers;
    tickers.reserve(calResult.size());
    for (const auto& stock: calResult) {
        tickers.push_back(stock.first);
    }
    portfolio.tickers = tickers;
    std::vector<double> expectedReturns = calculator.calculateExpectedReturn(calResult);
    portfolio.expectedReturn = portfolioReturn(
            portfolio.weights,
            expectedReturns);
    portfolio.expectedRisk = portfolioRisk(
            portfolio.weights,
            covarianceMatrix);
    return portfolio;
}

std::vector<double> PortfolioOptimizer::solveQuadraticProgram(
        const std::vector<std::vector<double>>& covarianceMatrix,
        const std::vector<std::vector<double>>& activeMatrix,
        const std::vector<double>& bVector,
        std::vector<double>& xVector,
        const std::vector<double>& cVector
        ) {
    ActiveSetSolver solver;
    return solver.solve(covarianceMatrix, activeMatrix, bVector, xVector, cVector);
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

