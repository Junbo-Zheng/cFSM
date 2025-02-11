cmake_minimum_required(VERSION 3.23)

project(fsm)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Werror -Wno-format -g)

add_library(fsm STATIC fsm.c)
