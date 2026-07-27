#pragma once

#include "../include/StockData.h"
#include <vector>
#include <map>

/**
 * @class ReturnCalculator
 * @brief Calculates investment returns from historical stock prices.
 *
 * This class provides methods for converting a sequence of stock prices
 * into a sequence of returns. The calculated returns will later be used
 * to compute expected return, covariance matrix, and portfolio optimization.
 */
class ReturnCalculator {
    public:
    /**
     * @brief Calculate the return series of a stock.
     *
     * This function receives historical price data of a single stock
     * and calculates the return between every two consecutive trading days.
     *
     * Formula:
     *
     *      R = (Pt - Pt-1) / Pt-1
     *
     * where
     *      Pt   : current day's adjusted closing price
     *      Pt-1 : previous day's adjusted closing price
     *
     * @param stocks Historical price data of one stock.
     *
     * @return A vector containing the return of each trading day.
     */
     std::map<std::string, std::vector<double>> calculate(const std::vector<StockData>& stocks);

    private:
    /**
     * @brief Calculate the return between two consecutive prices.
     *
     * Formula:
     *
     *      R = (Pt - Pt-1) / Pt-1
     *
     * Example:
     *
     *      Previous Price = 100
     *      Current Price  = 105
     *
     *      Return = (105 - 100) / 100 = 0.05 (5%)
     *
     * @param previousPrice Price at previous trading day.
     * @param currentPrice  Price at current trading day.
     *
     * @return Price return.
     */
    double calculatePriceReturn(double previousPrice, double currentPrice);
};