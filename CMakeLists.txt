cmake_minimum_required(VERSION 3.19)
project(logger)

set(CMAKE_CXX_STANDARD 17)

add_library(logger SHARED Logger.cpp Logger.h)
