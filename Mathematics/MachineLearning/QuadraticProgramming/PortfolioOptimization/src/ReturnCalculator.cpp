#include "../include/ReturnCalculator.h"
#include "../include/StockRepository.h"

#include <map>
#include <vector>

std::map<std::string, std::vector<double>> ReturnCalculator::calculate(
        const std::vector<StockData>& stocks) {
    StockRepository repository;
    std::map<std::string, std::vector<StockData>> groupedStocks = repository.groupByTicker(stocks);
    std::map<std::string, std::vector<double>> result;
    for (const auto& groupedStock : groupedStocks) {
        for (int i = 0; i < groupedStock.second.size() - 1; i++) {
            result[groupedStock.first].push_back(
                    calculatePriceReturn(
                            groupedStock.second[i + 1].close,
                            groupedStock.second[i].close));
        }
    }
    return result;
}


double ReturnCalculator::calculatePriceReturn(
        double previousPrice,
        double currentPrice
        ) {
    return (currentPrice - previousPrice) / previousPrice;
}