#include <iostream>

#include <map>
#include <vector>


#include "../include/CsvReader.h"
#include "../include/ReturnCalculator.h"
#include "../include/CovarianceMatrix.h"
#include "../include/PortfolioOptimizer.h"

int main() {

    CsvReader reader;
    ReturnCalculator calculator;
    CovarianceMatrix coMatrix;
    PortfolioOptimizer portfolioOptimizer;

    std::vector<StockData> stocks = reader.load("../data/stocks.csv");

    std::cout << "Total records: " << stocks.size() << std::endl;

    std::map<std::string, std::vector<double>> calResult = calculator.calculate(stocks);

    for (int i = 0; i < calResult.size(); i++) {
         std::cout << "Total grouped records: " << calResult["A"][i] << std::endl;
    }

    std::vector<std::vector<double>> matrix = coMatrix.calculate(calResult);

    Portfolio portfolio =
            portfolioOptimizer.optimize(calResult, matrix);
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