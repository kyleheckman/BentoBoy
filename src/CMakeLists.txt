add_library(isa gb_isa.c)
target_include_directories(isa PUBLIC ${CMAKE_SOURCE_DIR}/inc)

add_library(op gb_opcodes.c)
target_include_directories(op PUBLIC ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(op isa)

add_library(vout gb_video.c)
target_include_directories(vout PUBLIC ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(vout raylib)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} isa op vout)