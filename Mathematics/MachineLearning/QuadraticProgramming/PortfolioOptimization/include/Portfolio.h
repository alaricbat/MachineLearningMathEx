#pragma once

#include <string>
#include <vector>

class Portfolio {
    public:
        std::vector<std::string> tickers;
        std::vector<double> weights;
        double expectedReturn;
        double expectedRisk;
};