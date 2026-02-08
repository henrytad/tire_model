cmake_minimum_required(VERSION 3.15)

project(tire_model VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

############################################################
# Create tire_model static library
############################################################

# Generate the static library from the library sources
add_library(tire_model STATIC 
    src/mf612/tire_mf612.cpp
    src/internal/tire_file_parser.cpp
    src/tire_model.cpp
)

target_include_directories(tire_model
    PUBLIC 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Set compile features
target_compile_features(tire_model PUBLIC cxx_std_20)

# Optional: Set output directory for library
set_target_properties(tire_model PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

############################################################
# Example executable
############################################################

add_executable(tire_model_example 
    examples/example_usage.cpp
)

target_link_libraries(tire_model_example
    PRIVATE 
        tire_model
)

# Copy the sample.tir file to the build directory so the example can find it
add_custom_command(TARGET tire_model_example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/examples/sample.tir
    ${CMAKE_BINARY_DIR}/sample.tir
    COMMENT "Copying sample.tir to build directory"
)