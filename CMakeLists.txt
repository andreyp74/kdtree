cmake_minimum_required(VERSION 3.16)

project(kdtree)

include_directories(include)

file(GLOB_RECURSE PROJECT_SRC
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

