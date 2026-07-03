cmake_minimum_required(VERSION 3.27)
project(Mathematics)

set(CMAKE_CXX_STANDARD 17)

add_executable(Mathematics main.cpp
        FindThePoint/FindDistancePoint.cpp
        FindThePoint/FindDistancePoint.cpp
        DualLagrange/ExecuteDualLagrange.cpp)
