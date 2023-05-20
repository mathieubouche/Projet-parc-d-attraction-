cmake_minimum_required(VERSION 3.23)
project(piano_tiles C)

set(CMAKE_C_STANDARD 99)

add_executable(piano_tiles main.c)

target_link_libraries(piano_tiles -lmingw32 -lalleg44)
