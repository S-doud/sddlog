set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(example1 example1.cpp)
add_executable(example2 example2.cpp)
add_executable(example3 example3.cpp)

target_link_libraries(example1 sddlog)
target_link_libraries(example2 sddlog)
target_link_libraries(example3 sddlog)
