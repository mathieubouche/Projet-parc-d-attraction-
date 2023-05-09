cmake_minimum_required(VERSION 3.23)
project(SAMIL C)

set(CMAKE_C_STANDARD 99)

add_executable(SAMIL main.c)
target_link_libraries(SAMIL -lmingw32 -lalleg44)
