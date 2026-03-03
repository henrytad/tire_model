cmake_minimum_required(VERSION 3.15)

project(tire_model VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

############################################################
# Options
############################################################

# Default to building tests/examples only when this is the top-level project.
# Consumers via FetchContent/add_subdirectory get only the library.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(_is_top_level ON)
else()
    set(_is_top_level OFF)
endif()

option(TIRE_MODEL_BUILD_TESTS    "Build unit tests"       ${_is_top_level})
option(TIRE_MODEL_BUILD_EXAMPLES "Build example programs"  ${_is_top_level})

############################################################
# Create tire_model static library
############################################################

add_library(tire_model STATIC
    src/mf612/tire_mf612.cpp
    src/internal/tire_file_parser.cpp
    src/tire_model.cpp
)

target_include_directories(tire_model
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(tire_model PUBLIC cxx_std_20)

set_target_properties(tire_model PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

############################################################
# Example executable
############################################################

if(TIRE_MODEL_BUILD_EXAMPLES)

    add_executable(tire_model_example
        examples/example_usage.cpp
    )

    target_link_libraries(tire_model_example
        PRIVATE
            tire_model
    )

    add_custom_command(TARGET tire_model_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/examples/sample.tir
            ${CMAKE_BINARY_DIR}/sample.tir
        COMMENT "Copying sample.tir to build directory"
    )

endif()

############################################################
# Tests
############################################################

if(TIRE_MODEL_BUILD_TESTS)

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    include(GoogleTest)
    enable_testing()

    add_executable(tire_model_tests
        tests/test_tire_mf612.cpp
    )

    target_link_libraries(tire_model_tests
        PRIVATE
            tire_model
            GTest::gtest_main
    )

    gtest_discover_tests(tire_model_tests)

endif()
