cmake_minimum_required(VERSION 3.20)
project(blackjack LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(blackjack_backend
    src/backend/deck.cpp
    src/backend/hand.cpp
    src/backend/game.cpp)
target_include_directories(blackjack_backend PUBLIC include/backend)
target_compile_options(blackjack_backend PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion -Wshadow)