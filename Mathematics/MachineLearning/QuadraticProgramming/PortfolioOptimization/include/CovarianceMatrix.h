#pragma once

#include <vector>
#include <map>

class CovarianceMatrix {
public:
    /**
     * @brief Build covariance matrix from stock return series.
     *
     * Input:
     *      AAPL -> [r1, r2, ...]
     *      AAL  -> [r1, r2, ...]
     *      A    -> [r1, r2, ...]
     *
     * Output:
     *      NxN covariance matrix.
     */
    std::vector<std::vector<double>> calculate(const std::map<std::string, std::vector<double>>& returns);

private:
    /**
     * @brief Calculate covariance between two return series.
     */
    double covariance(const std::vector<double>& x,const std::vector<double>& y);
};