cmake_minimum_required(VERSION 3.6)
project(cs210_sem2)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(cs210_sem2 ${SOURCE_FILES})

set_target_properties( cs210_sem2
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
