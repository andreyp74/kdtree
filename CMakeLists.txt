cmake_minimum_required(VERSION 3.14)

project(kdtree CXX C)

add_subdirectory("external/gtest")

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_WIN32_WINNT=0x0601)
    add_compile_options("/std:c++latest")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /MP")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /MD")
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG /OPT:REF /OPT:ICF")
endif()

include_directories(include)

file(GLOB_RECURSE PROJECT_SRC
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

include_directories(
    "${GTEST_INCLUDE_DIRS}"
    #"${GMOCK_INCLUDE_DIRS}"
)

link_directories(
    "${CMAKE_BINARY_DIR}"
)

enable_testing()

option (BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    include(kdtree-tests.cmake)
endif()

