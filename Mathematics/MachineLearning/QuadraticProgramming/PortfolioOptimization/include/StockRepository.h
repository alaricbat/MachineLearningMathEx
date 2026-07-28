#pragma once

#include <map>
#include <string>
#include <vector>

#include "../include/StockData.h"

/**
 * @class StockRepository
 * @brief Organizes historical stock data by ticker symbol.
 *
 * This class converts the raw stock records loaded from CSV
 * into groups of historical data for each stock.
 */
class StockRepository {
public:

    /**
     * @brief Group stock records by ticker symbol.
     *
     * Input:
     *      vector<StockData>
     *
     * Output:
     *      map<Ticker, vector<StockData>>
     *
     * Example:
     *
     *      AAPL -> [ ... ]
     *      AAL  -> [ ... ]
     *      A    -> [ ... ]
     */
    std::map<std::string, std::vector<StockData>> groupByTicker(const std::vector<StockData>& stocks);

};