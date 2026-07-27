cmake_minimum_required(VERSION 3.27)
project(Mathematics)

set(CMAKE_CXX_STANDARD 17)

add_executable(Mathematics main.cpp
        Basic/FindThePoint/FindDistancePoint.cpp
        Basic/FindThePoint/FindDistancePoint.cpp
        MachineLearning/DualLagrange/ExecuteDualLagrange.cpp
        Basic/SummingTheNSeries/SummingNSeries.cpp
        Basic/MovingTiles/MovingTileMath.cpp
        MachineLearning/QuadraticProgramming/QuadraticProgramming.cpp
        MachineLearning/QuadraticProgramming/PortfolioOptimization/include/StockData.h
        MachineLearning/QuadraticProgramming/PortfolioOptimization/include/StockData.h
        MachineLearning/QuadraticProgramming/PortfolioOptimization/include/CsvReader.h
        MachineLearning/QuadraticProgramming/PortfolioOptimization/include/ReturnCalculator.h
        MachineLearning/QuadraticProgramming/PortfolioOptimization/include/Statistics.h
        MachineLearning/QuadraticProgramming/PortfolioOptimization/include/CovarianceMatrix.h
        MachineLearning/QuadraticProgramming/PortfolioOptimization/include/Portfolio.h
        MachineLearning/QuadraticProgramming/PortfolioOptimization/include/PortfolioOptimizer.h
        MachineLearning/QuadraticProgramming/PortfolioOptimization/src/main.cpp
        MachineLearning/QuadraticProgramming/PortfolioOptimization/src/CsvReader.cpp
)
