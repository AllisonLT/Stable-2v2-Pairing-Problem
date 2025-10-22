cmake_minimum_required(VERSION 4.0.2)
project(SC2_2v2_Pairing VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SRC_FILES 
    src/model/*.cpp
    src/generator/*.cpp
    src/solver/*.cpp
    src/backup/*.cpp
    src/utils/*.cpp
    src/io/*.cpp
)

# Main executable
add_executable(SC2_2v2_Pairing src/main.cpp ${SRC_FILES})

# # Google Test configuration
# enable_testing()
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# # Test files
# file(GLOB_RECURSE TEST_FILES test/*.cpp)
# add_executable(SC2_2v2_Pairing_Tests ${TEST_FILES} ${SRC_FILES})
# target_link_libraries(SC2_2v2_Pairing_Tests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

# Copy config files to build directory
configure_file(config/PairingConfig.ini ${CMAKE_BINARY_DIR}/config/PairingConfig.ini COPYONLY)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# VS2022 specific settings
if(MSVC)
    target_compile_options(SC2_2v2_Pairing PRIVATE /W4 /MD)
    # target_compile_options(SC2_2v2_Pairing_Tests PRIVATE /W4 /MD)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SC2_2v2_Pairing)
endif()