cmake_minimum_required(VERSION 3.2)
project(gtest_builder C CXX)

include(ExternalProject)

ExternalProject_Add(googletest
    URL https://github.com/google/googletest/archive/release-1.8.1.zip
    #URL_MD5 ef5e700c8a0f3ee123e2e0209b8b4961
    CMAKE_ARGS -DBUILD_GMOCK=OFF
               -Dgtest_force_shared_crt=ON
               -Dgtest_build_tests=OFF
               -DBUILD_SHARED_LIBS=OFF
               -DLIBRARY_OUTPUT_PATH:PATH=${CMAKE_BINARY_DIR}
               -DCMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}
               -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}

    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    INSTALL_COMMAND ""
    DOWNLOAD_DIR "${CMAKE_SOURCE_DIR}/.downloaded"
)

# Specify include dir
ExternalProject_Get_Property(googletest SOURCE_DIR)
set(GTEST_INCLUDE_DIRS ${SOURCE_DIR}/googletest/include PARENT_SCOPE)

set(GTEST_LIBRARIES
  ${CMAKE_STATIC_LIBRARY_PREFIX}gtestd${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${CMAKE_STATIC_LIBRARY_PREFIX}gtest_maind${CMAKE_STATIC_LIBRARY_SUFFIX}
  PARENT_SCOPE
)
