add_executable(reader_test reader_test.cpp)
add_executable(iterator_test iterator_test.cpp)
add_executable(solver_test solver_test.cpp)

target_link_libraries(reader_test PRIVATE reader)
target_link_libraries(iterator_test PRIVATE solver)
target_link_libraries(solver_test PRIVATE solver)

add_test(NAME run_reader_test COMMAND reader_test)
add_test(NAME run_iterator_test COMMAND iterator_test)
add_test(NAME run_solver_test COMMAND solver_test)
