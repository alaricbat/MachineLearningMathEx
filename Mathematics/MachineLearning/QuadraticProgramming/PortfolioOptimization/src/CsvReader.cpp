#include "../include/CsvReader.h"

#include <fstream>
#include <sstream>

std::vector<StockData> CsvReader::load(const std::string& filename) {
    std::vector<StockData> stocks;
    std::fstream file(filename);
    if (!file.is_open()) {
        return stocks;
    }
    std::string line;
    getline(file, line);
    while(getline(file, line)) {
        StockData stock = parseLine(line);
        stocks.push_back(stock);
    }
    file.close();
    return stocks;
}

StockData CsvReader::parseLine(const std::string& line) {

    StockData stock;

    std::stringstream ss(line);

    std::string value;

    std::getline(ss, stock.ticker, ',');

    std::getline(ss, stock.date, ',');

    std::getline(ss, value, ',');
    stock.open = std::stod(value);

    std::getline(ss, value, ',');
    stock.high = std::stod(value);

    std::getline(ss, value, ',');
    stock.low = std::stod(value);

    std::getline(ss, value, ',');
    stock.close = std::stod(value);

    std::getline(ss, value, ',');
    stock.adjClose = std::stod(value);

    std::getline(ss, value, ',');
    stock.volume = std::stol(value);

    return stock;
}

