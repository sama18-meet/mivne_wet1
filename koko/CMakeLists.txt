cmake_minimum_required(VERSION 3.20)
project(github)

set(CMAKE_CXX_STANDARD 14)

add_executable(github main.cpp avl.h Player.h Player.cpp Vec2D.h Vec2D.cpp Group.cpp Group.h PlayersManager.cpp PlayersManager.h)
