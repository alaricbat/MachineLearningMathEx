#pragma once

#include "Portfolio.h"

class PortfolioOptimizer {
    public:
        Portfolio optimizer(
                const std::vector<std::vector<double>>& covariance,
                const std::vector<std::double>& expectedReturn);
};