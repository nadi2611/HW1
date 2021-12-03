cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled avlTree.h group.h group.cpp playerLevel.cpp playerLevel.h playerId.cpp playerId.h hw1.cpp playersManager.cpp playersManager.h hw1.h)
