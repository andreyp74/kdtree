set(PROJECT_TEST_NAME ${PROJECT_NAME}.test)

include_directories(include tests "${GTEST_INCLUDE_DIRS}")

file(GLOB_RECURSE TEST_SRC
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.hpp)

file(GLOB_RECURSE EXTERNAL_SRC
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

list(REMOVE_ITEM EXTERNAL_SRC src/main.cpp)

source_group(Sources FILES ${EXTERNAL_SRC})
source_group(Tests FILES ${TEST_SRC})

add_executable(${PROJECT_TEST_NAME} ${TEST_SRC} ${EXTERNAL_SRC})
add_dependencies(${PROJECT_TEST_NAME} googletest)

target_link_libraries(
    ${PROJECT_TEST_NAME}
    ${GTEST_LIBRARIES}
)

#set_target_properties(${PROJECT_TEST_NAME}
#    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_test(NAME     ${PROJECT_TEST_NAME}
         COMMAND  ${PROJECT_TEST_NAME})
