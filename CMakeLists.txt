# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(FirstImage VERSION 1.0)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable threading support
find_package(Threads REQUIRED)

# Enable testing
enable_testing()

# Add subdirectories
add_subdirectory(tests)
add_subdirectory(src)
