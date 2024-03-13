add_executable(reader_test reader_test.cpp)
target_link_libraries(reader_test PRIVATE reader)

add_test(NAME run_reader_test COMMAND reader_test)
