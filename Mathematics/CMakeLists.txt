cmake_minimum_required(VERSION 3.27)
project(Mathematics)

set(CMAKE_CXX_STANDARD 17)

add_executable(Mathematics main.cpp
        Basic/FindThePoint/FindDistancePoint.cpp
        Basic/FindThePoint/FindDistancePoint.cpp
        MachineLearning/DualLagrange/ExecuteDualLagrange.cpp
        Basic/SummingTheNSeries/SummingNSeries.cpp
        Basic/MovingTiles/MovingTileMath.cpp)
