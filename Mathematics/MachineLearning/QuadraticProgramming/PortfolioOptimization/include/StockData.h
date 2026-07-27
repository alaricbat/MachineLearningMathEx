#pragma once

#include <string>

class StockData {
    public:
        std::string ticker;
        std::string date;
        double open;
        double high;
        double low;
        double close;
        double adjClose;
        long volume;
};