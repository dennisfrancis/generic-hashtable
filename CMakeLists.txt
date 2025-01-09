cmake_minimum_required(VERSION 3.10)

project(generic_hashtable VERSION 1.0.0)

# specify the C++ standard
set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

add_library(gendll dll.c)
target_include_directories(gendll PUBLIC ${CMAKE_SOURCE_DIR})

add_library(genhash hash.c)
target_include_directories(genhash PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(genhash gendll)

add_executable(test_gendll test_ll.c)
target_include_directories(test_gendll PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(test_gendll gendll)

add_executable(test_genhash test_hash.c)
target_include_directories(test_genhash PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(test_genhash genhash)

add_custom_command(TARGET test_gendll POST_BUILD
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_gendll > ${CMAKE_CURRENT_BINARY_DIR}/test_gendll.log 2>&1
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "[TEST] Running doubly linked list tests...")

add_custom_command(TARGET test_genhash POST_BUILD
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_genhash > ${CMAKE_CURRENT_BINARY_DIR}/test_genhash.log 2>&1
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "[TEST] Running hashtable tests...")

