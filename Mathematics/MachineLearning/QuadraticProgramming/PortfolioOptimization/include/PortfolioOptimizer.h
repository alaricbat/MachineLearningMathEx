#pragma once

#include "Portfolio.h"
#include "map"

class PortfolioOptimizer {
public:
    Portfolio optimize(
            const std::map<std::string, std::vector<double>>& stocks,
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