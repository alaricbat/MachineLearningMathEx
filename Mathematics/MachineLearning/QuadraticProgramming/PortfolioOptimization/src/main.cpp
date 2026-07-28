#include <iostream>

#include <map>
#include <vector>

#include "../include/CsvReader.h"
#include "../include/ReturnCalculator.h"

int main() {

    CsvReader reader;
    ReturnCalculator calculator;

    std::vector<StockData> stocks = reader.load("../data/stocks.csv");

    std::cout << "Total records: " << stocks.size() << std::endl;

    std::map<std::string, std::vector<double>> calResult = calculator.calculate(stocks);

    for (int i = 0; i < calResult.size(); i++) {
         std::cout << "Total grouped records: " << calResult["A"][i] << std::endl;
    }


    return 0;
}