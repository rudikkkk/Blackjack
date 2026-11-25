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

add_executable(blackjack_exe
    src/main.cpp
    src/frontend/app.cpp
    src/frontend/screen.cpp
    src/frontend/screen_manager.cpp
    src/frontend/player_panel.cpp
    src/frontend/card_renderer.cpp
    src/frontend/screens/menu_screen.cpp
    src/frontend/screens/rules_screen.cpp
    src/frontend/screens/player_count_screen.cpp
    src/frontend/screens/game_screen.cpp
    src/frontend/screens/result_screen.cpp
)
target_include_directories(blackjack_exe PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(blackjack_exe PRIVATE blackjack_backend)
target_link_libraries(blackjack_exe PRIVATE FrontUI::frontui)
if(MSVC)
    target_compile_options(blackjack_exe PRIVATE /utf-8)
endif()
target_compile_definitions(blackjack_exe PRIVATE
    ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/include/assets"
)