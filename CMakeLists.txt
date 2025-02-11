cmake_minimum_required(VERSION 3.23)

project(simple)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib)

add_compile_options(-Wall -Wextra -Werror -Wno-format -g)

add_executable(simple simple.c)

target_link_libraries(simple fsm)

target_include_directories(simple PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
