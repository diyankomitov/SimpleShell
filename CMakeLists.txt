cmake_minimum_required(VERSION 2.8)
project(cs210_sem2)

set(CMAKE_C_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCE_FILES shell.c shell_input.c)
add_executable(cs210_sem2 ${SOURCE_FILES})

set_target_properties( cs210_sem2
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
