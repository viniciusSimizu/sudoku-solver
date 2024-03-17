cmake_minimum_required(VERSION 3.27.7)
project(estevan)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib)

enable_testing()
add_subdirectory(tests)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE reader solver writer)
