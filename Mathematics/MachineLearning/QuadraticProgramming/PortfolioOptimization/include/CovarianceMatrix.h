#pragma once

#include <vector>

class CovarianceMatrix {
    public:
        std::vector<std::vector<double>> calculate(
                const std::vector<std::vector<double>>& returns);
};