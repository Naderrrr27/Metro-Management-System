cmake_minimum_required(VERSION 3.28)
project(Metro)

set(CMAKE_CXX_STANDARD 17)

add_executable(Metro main.cpp
        metro.cpp
        metro.h
        line.cpp
        line.h
        station.cpp
        station.h
        Statistics.h
        Statistics.cpp
        subscription.cpp
        subscription.h
        wallet.h
        wallet.cpp
)

