cmake_minimum_required(VERSION 3.27)
project(MachineLearningMathEx)

set(CMAKE_CXX_STANDARD 14)

include_directories(Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/include)

add_executable(MachineLearningMathEx
        Mathematics/Basic/FindThePoint/FindDistancePoint.cpp
        Mathematics/Basic/MovingTiles/MovingTileMath.cpp
        Mathematics/Basic/SummingTheNSeries/SummingNSeries.cpp
        Mathematics/LLM/TransformerEncoderSim/src/PretrainedNLPModel.cpp
        Mathematics/LLM/TransformerEncoderSim/src/TextClassifier.cpp
        Mathematics/LLM/TransformerEncoderSim/src/TransformerEncoder.cpp
        Mathematics/LLM/TransformerEncoderSim/main.cpp
        Mathematics/MachineLearning/DualLagrange/ExecuteDualLagrange.cpp
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/include/ActiveSetSolver.h
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/include/CovarianceMatrix.h
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/include/CsvReader.h
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/include/KKTSolver.h
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/include/LinearSolver.h
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/include/MatrixSolver.h
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/include/Portfolio.h
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/include/PortfolioOptimizer.h
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/include/ReturnCalculator.h
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/include/Statistics.h
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/include/StockData.h
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/include/StockRepository.h
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/src/ActiveSetSolver.cpp
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/src/CovarianceMatrix.cpp
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/src/CsvReader.cpp
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/src/KKTSolver.cpp
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/src/LinearSolver.cpp
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/src/main.cpp
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/src/MatrixSolver.cpp
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/src/PortfolioOptimizer.cpp
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/src/ReturnCalculator.cpp
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/src/Statistics.cpp
        Mathematics/MachineLearning/QuadraticProgramming/PortfolioOptimization/src/StockRepository.cpp
        Mathematics/main.cpp
        Mathematics/LLM/TransformerEncoderSim/utils/Matrix.cpp)
