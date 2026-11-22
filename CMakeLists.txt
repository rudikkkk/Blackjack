cmake_minimum_required(VERSION 3.20)
project(blackjack LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/FrontUI)

add_library(blackjack_backend
    src/backend/deck.cpp
    src/backend/hand.cpp
    src/backend/game.cpp)
target_include_directories(blackjack_backend PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/backend)
target_compile_options(blackjack_backend PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion -Wshadow)

add_executable(blackjack_exe ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(blackjack_exe PRIVATE blackjack_backend)
target_link_libraries(blackjack_exe PRIVATE FrontUI::frontui)
target_compile_definitions(blackjack_exe PRIVATE
    ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/include/assets"
)