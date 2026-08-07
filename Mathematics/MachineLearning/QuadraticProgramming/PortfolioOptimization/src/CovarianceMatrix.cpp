#include "../include/CovarianceMatrix.h"
#include "../include/Statistics.h"

#include <map>

std::vector<std::vector<double>> CovarianceMatrix::calculate(const std::map<std::string, std::vector<double>> &returns) {
        const size_t n = returns.size();

        if (n == 0) return {};

        std::vector<std::vector<double>> matrix(
                n,
                std::vector<double>(n, 0.0));

        //Convert map to vector
        std::vector<std::pair<std::string, std::vector<double>>> stocks(
                returns.begin(),
                returns.end());

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                matrix[i][j] = covariance(
                        stocks[i].second,
                        stocks[j].second
                        );
            }
        }

        return matrix;
}

double CovarianceMatrix::covariance(const std::vector<double>& x,const std::vector<double>& y) {
    if (x.size() != y.size() || x.size() < 2) return 0.0;

    Statistics statistics;

    double mean_x = statistics.mean(x);
    double mean_y = statistics.mean(y);

    size_t n = x.size();
    double sum = 0.0;

    for (size_t i = 0; i < n; ++i) {
        double diff_x = x[i] - mean_x;
        double diff_y = y[i] - mean_y;
        sum += diff_x * diff_y;
    }

    return sum / static_cast<double>(n - 1);
}

