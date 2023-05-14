cmake_minimum_required(VERSION 3.23)
project(labyrinthe_a_merde C)

set(CMAKE_C_STANDARD 99)

add_executable(labyrinthe_a_merde main.c)

target_link_libraries(labyrinthe_a_merde -lmingw32 -lalleg44)

