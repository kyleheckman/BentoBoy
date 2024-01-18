add_library(isa gb_isa.c)
target_include_directories(isa PUBLIC ${CMAKE_SOURCE_DIR}/inc)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} isa)