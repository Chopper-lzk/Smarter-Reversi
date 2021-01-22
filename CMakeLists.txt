cmake_minimum_required(VERSION 3.10)
project(Smarter-Reversi)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(/usr/include/SDL2)
add_executable(reversi  ./src/main.cpp ./src/REVERSI.cpp ./src/SDLC.cpp)
target_link_libraries(reversi SDL2 SDL2_ttf SDL2_image)


