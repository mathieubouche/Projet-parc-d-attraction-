cmake_minimum_required(VERSION 3.23)
project(TP2 C)

set(CMAKE_C_STANDARD 23)

add_executable(TP2 main.c)

target_link_libraries(TP2 -lmingw32 -lalleg44)
