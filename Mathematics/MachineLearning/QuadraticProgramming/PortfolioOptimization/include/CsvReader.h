#pragma once

#include <vector>
#include <string>
#include "StockData.h"

class CsvReader {
    public:
        std::vector<StockData> load(const std::string& filename);

    private:
        StockData parseLine(const std::string& line);

};