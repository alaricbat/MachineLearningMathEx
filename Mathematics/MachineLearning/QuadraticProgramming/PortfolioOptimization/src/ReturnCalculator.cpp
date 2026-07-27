#include "../include/ReturnCalculator.h"

std::map<std::string, std::vector<double>> ReturnCalculator::calculate(
        const std::vector<StockData>& stocks) {
    std::map<std::string, std::vector<double>> result;

    return result;
}


double ReturnCalculator::calculatePriceReturn(
        double previousPrice,
        double currentPrice
        ) {
    return (currentPrice - previousPrice) / previousPrice;
}