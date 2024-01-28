cmake_minimum_required(VERSION 3.22.1)

# Sources and test naming
set(TEST_NAME "run_tests")
set(TEST_SRCS demo_tests.c)
set(FRAMEWORK Unity)

# Assemble the testing framework
add_library(
    ${FRAMEWORK} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendors/Unity/src/unity.c
)
target_include_directories(
    ${FRAMEWORK} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendors/Unity/src
)

# Create test executable
add_executable(${TEST_NAME} ${TEST_SRCS})
target_include_directories(
    ${TEST_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(
    ${TEST_NAME} PRIVATE
    ${FRAMEWORK}
    ${COMMON_LIB}
    ${DEPENDENCIES}
)
set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
set_target_properties(
    ${TEST_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)

# Run tests
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})