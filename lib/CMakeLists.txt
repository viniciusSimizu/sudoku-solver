add_library(iterator iterator/iterator.cpp)
add_library(workspace workspace/workspace.cpp)
add_library(reader reader/reader.cpp)
add_library(writer writer/writer.cpp)
add_library(solver solver/solver.cpp)

target_link_libraries(reader PUBLIC workspace)
target_link_libraries(writer PUBLIC workspace)
target_link_libraries(solver PUBLIC iterator)

target_include_directories(iterator PUBLIC ${CMAKE_CURRENT_LIST_DIR}/iterator)
target_include_directories(workspace PUBLIC ${CMAKE_CURRENT_LIST_DIR}/workspace)
target_include_directories(reader PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/reader
	${CMAKE_CURRENT_LIST_DIR}/workspace)
target_include_directories(writer PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/writer
	${CMAKE_CURRENT_LIST_DIR}/workspace)
target_include_directories(solver PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/solver
	${CMAKE_CURRENT_LIST_DIR}/iterator)
