cmake_minimum_required(VERSION 3.20)
project(wet1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic-errors -Werror")

add_executable(wet1 main1.cpp avl.h Player.h Player.cpp Vec2D.h Vec2D.cpp Group.cpp Group.h PlayersManager.cpp PlayersManager.h library1.h library1.cpp)
