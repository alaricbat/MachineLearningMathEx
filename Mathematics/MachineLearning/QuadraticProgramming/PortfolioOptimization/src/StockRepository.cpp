#include "../include/StockRepository.h"

std::map<std::string, std::vector<StockData>> StockRepository::groupByTicker(const std::vector<StockData>& stocks) {
    std::map<std::string, std::vector<StockData>> groupedStocks;
    for (const auto& stock : stocks) {
        groupedStocks[stock.ticker].push_back(stock);
    }
    return groupedStocks;
}