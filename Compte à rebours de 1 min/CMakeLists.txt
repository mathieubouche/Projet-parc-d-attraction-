cmake_minimum_required(VERSION 3.23)
project(2 C)

set(CMAKE_C_STANDARD 99)

add_executable(2 main.c)
target_link_libraries (2 -lmingw32 -lalleg44)