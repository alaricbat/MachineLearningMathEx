#include <iostream>

#include "../include/CsvReader.h"

int main() {

    CsvReader reader;

    std::vector<StockData> stocks = reader.load("../data/stocks.csv");

    std::cout << "Total records: " << stocks.size() << std::endl;

    return 0;
}