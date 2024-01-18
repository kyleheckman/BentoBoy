cmake_minimum_required(VERSION 3.22)

project(bentoboy 
    LANGUAGES C)

set(C_STANDARD 99)

include(CTest)
enable_testing()

add_subdirectory(src)
add_subdirectory(test)