#pragma once

#include "Portfolio.h"
#include "StockData.h"
#include "map"

class PortfolioOptimizer {
public:
    Portfolio optimize(const std::vector<StockData>& stocks);

private:
    std::vector<double> solveQuadraticProgram(
            const std::vector<std::vector<double>>& covarianceMatrix,
            const std::vector<std::vector<double>>& activeMatrix,
            const std::vector<double>& bVector,
            std::vector<double>& xVector,
            const std::vector<double>& cVector);

    bool isFeasible(const std::vector<double>& weights);

    double portfolioRisk(
            const std::vector<double>& weights,
            const std::vector<std::vector<double>>& covarianceMatrix);

    double portfolioReturn(
            const std::vector<double>& weights,
            const std::vector<double>& expectedReturns);
};