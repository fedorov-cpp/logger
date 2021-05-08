cmake_minimum_required(VERSION 3.19)
project(logger)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_LIST_DIR})
add_library(logger SHARED Logger.cpp Logger.hpp)

if (TEST_ON)
    message("Tests turned on.")
    find_package(Catch2 REQUIRED)
    add_executable(tests test.cpp)
    target_link_libraries(tests PRIVATE Catch2::Catch2 logger)
endif()