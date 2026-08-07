#include "../include/Statistics.h"

#include "vector"
#include "numeric"
#include "cmath"


double Statistics::mean(const std::vector<double>& data) {
    if (data.empty()) {
        return 0.0;
    }
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

double Statistics::variance(const std::vector<double> &data) {
    if (data.empty()) return 0.0;
    double m = mean(data);
    double sum_sq_diff = std::accumulate(data.begin(),
                                         data.end(),
                                         0.0,
                                         [m](double acc, double val) {
        double diff = val - m;
        return acc + (diff * diff);
    });
    return sum_sq_diff / data.size();
}

double Statistics::standardDeviation(const std::vector<double> &data) {
    return std::sqrt(variance(data));
}
