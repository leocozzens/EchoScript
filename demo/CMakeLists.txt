cmake_minimum_required(VERSION 3.22.1)

# Sources and includes
set(DEMO_TARGET demo)
set(DEMO_SRCS demo.c str.c)
set(DEMO_NAME ${PROJECT_NAME}_demo)

set(
    DEMO_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
list(TRANSFORM DEMO_SRCS PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

# Demo executable
add_executable(${DEMO_NAME} ${DEMO_SRCS})
target_include_directories(
    ${DEMO_NAME} PRIVATE
    ${DEMO_INCLUDES}
)
set_target_properties(
    ${DEMO_NAME} PROPERTIES
    EXCLUDE_FROM_ALL TRUE
)
add_custom_target(
    ${DEMO_TARGET}
    COMMAND ${DEMO_NAME} ${BIN_DIR}/${PROJECT_NAME}
)
add_dependencies(
    ${DEMO_TARGET}
    ${PROJECT_NAME}
    ${DEMO_NAME}
)