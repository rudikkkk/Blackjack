cmake_minimum_required(VERSION 3.20)
project(FrontUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(FLTK REQUIRED)

add_library(frontui
    src/widget/widget.cpp
    src/widget/controls.cpp
    src/widget/group.cpp
    src/layout/layout.cpp
    src/window/window.cpp
    src/animation/animation.cpp
)
add_library(FrontUI::frontui ALIAS frontui)
target_include_directories(frontui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(frontui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(frontui PRIVATE ${FLTK_LIBRARIES})
target_include_directories(frontui SYSTEM PRIVATE ${FLTK_INCLUDE_DIR})