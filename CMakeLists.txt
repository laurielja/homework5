cmake_minimum_required(VERSION 4.2)
project(TSP)

set(CMAKE_CXX_STANDARD 26)

add_executable(TSP main.cpp
        checker.cpp
        BB.cpp
	CP.cpp
	DFS.cpp
	DP.cpp
	EM.cpp
)
