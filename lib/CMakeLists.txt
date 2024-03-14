add_library(include INTERFACE)
add_library(reader reader.cpp)
add_library(solver solver.cpp)

target_include_directories(include INTERFACE .)

target_link_libraries(reader PUBLIC include)
target_link_libraries(solver PUBLIC include)
