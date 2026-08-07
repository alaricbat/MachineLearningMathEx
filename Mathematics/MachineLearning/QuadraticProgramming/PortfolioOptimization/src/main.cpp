#include <iostream>

#include <map>
#include <vector>


#include "../include/CsvReader.h"
#include "../include/ReturnCalculator.h"
#include "../include/CovarianceMatrix.h"
#include "../include/LinearSolver.h"
#include "../include/PortfolioOptimizer.h"

int main() {

    CsvReader reader;
    ReturnCalculator calculator;
    CovarianceMatrix coMatrix;
    LinearSolver linearSolver;
    PortfolioOptimizer portfolioOptimizer;

    std::vector<StockData> stocks = reader.load("../data/stocks.csv");

    std::cout << "Total records: " << stocks.size() << std::endl;

    std::map<std::string, std::vector<double>> calResult = calculator.calculate(stocks);

    for (int i = 0; i < calResult.size(); i++) {
         std::cout << "Total grouped records: " << calResult["A"][i] << std::endl;
    }

    std::vector<std::vector<double>> matrix = coMatrix.calculate(calResult);

    Portfolio pofolio =
            portfolioOptimizer.optimize(calculator.calculateExpectedReturn(calResult), matrix);

    std::cout << "Risk : " << pofolio.expectedRisk << std::endl;
    std::cout << "Return : " << pofolio.expectedReturn << std::endl;

    return 0;
}