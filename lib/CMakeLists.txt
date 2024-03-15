add_library(reader reader/reader.cpp)
add_library(solver solver/solver.cpp)

target_include_directories(reader PUBLIC ${CMAKE_CURRENT_LIST_DIR}/reader)
target_include_directories(solver PUBLIC ${CMAKE_CURRENT_LIST_DIR}/solver)
