#pragma once

#include <vector>

class Statistics {
    public:
        double mean(const std::vector<double>& data);
        double variance(const std::vector<double>& data);
        double standardDeviation(const std::vector<double>& data);
};