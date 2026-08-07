#pragma once

#include "Portfolio.h"

class PortfolioOptimizer {
public:
    Portfolio optimize(
            const std::vector<double>& expectedReturns,
            const std::vector<std::vector<double>>& covarianceMatrix);

private:
    std::vector<double> solveQuadraticProgram(
            const std::vector<std::vector<double>>& covarianceMatrix);

    bool isFeasible(const std::vector<double>& weights);

    double portfolioRisk(
            const std::vector<double>& weights,
            const std::vector<std::vector<double>>& covarianceMatrix);

    double portfolioReturn(
            const std::vector<double>& weights,
            const std::vector<double>& expectedReturns);
};