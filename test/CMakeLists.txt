
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

aux_source_directory(. SRC_LIST)

add_executable(sddtest ${SRC_LIST})

target_link_libraries(sddtest sddlog)

add_test(NAME sddtest COMMAND sddtest)
