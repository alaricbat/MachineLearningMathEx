#include <iostream>

#include <vector>


#include "../include/CsvReader.h"
#include "../include/PortfolioOptimizer.h"

int main() {

    CsvReader reader;
    PortfolioOptimizer portfolioOptimizer;

    std::vector<StockData> stocks = reader.load("../data/stocks.csv");
    std::cout << "Total records: " << stocks.size() << std::endl;
    Portfolio portfolio =
            portfolioOptimizer.optimize(stocks);
    std::cout << "\n===== Optimal Portfolio =====\n";

    for (size_t i = 0; i < portfolio.weights.size(); ++i)
    {
        std::cout
                << portfolio.tickers[i]
                << " : "
                << portfolio.weights[i] * 100
                << "%\n";
    }
    std::cout << "Risk : " << portfolio.expectedRisk << std::endl;
    std::cout << "Return : " << portfolio.expectedReturn << std::endl;

    return 0;
}