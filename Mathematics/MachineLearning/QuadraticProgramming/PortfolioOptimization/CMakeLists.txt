cmake_minimum_required(VERSION 3.20)

project(PortfolioOptimization)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(PortfolioOptimization
        src/main.cpp
        src/CsvReader.cpp
        src/ReturnCalculator.cpp
        include/StockData.h
        include/CsvReader.h
        include/ReturnCalculator.h
        include/Statistics.h
        include/CovarianceMatrix.h
        include/Portfolio.h
        include/PortfolioOptimizer.h
        src/ReturnCalculator.cpp
        include/StockRepository.h
        src/StockRepository.cpp
)