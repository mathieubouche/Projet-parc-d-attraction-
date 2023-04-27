cmake_minimum_required(VERSION 3.23)
project(TEST C)

set(CMAKE_C_STANDARD 99)

add_executable(TEST main.c)
target_link_libraries(TEST -lmingw32 -lalleg44)
