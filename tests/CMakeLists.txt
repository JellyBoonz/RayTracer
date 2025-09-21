cmake_minimum_required(VERSION 3.10)
project(TupleTests)
enable_testing()  # Enable CTest functionality

# Include GoogleTest using FetchContent
include(FetchContent)
FetchContent_Declare(
  gtest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(gtest)

# Include directories for your headers
include_directories(${CMAKE_SOURCE_DIR}/src)

# Create shared library for ray tracer components
add_library(RayTracerLib STATIC
    ../src/Tuple.cpp
    ../src/Matrix.cpp
    ../src/Ray.cpp
    ../src/Sphere.cpp
    ../src/Pattern.cpp
    ../src/Noise.cpp
    ../src/Light.cpp
    ../src/World.cpp
    ../src/Transforms.cpp
)

# Tuple Tests
add_executable(TupleTests TupleTests.cpp)
target_link_libraries(TupleTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME TupleTests COMMAND TupleTests)

# Canvas Tests
add_executable(CanvasTests CanvasTests.cpp)
target_link_libraries(CanvasTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME CanvasTests COMMAND CanvasTests)

# Camera Tests
add_executable(CameraTests CameraTests.cpp)
target_link_libraries(CameraTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME CameraTests COMMAND CameraTests)

# Color Tests
add_executable(ColorTests ColorTests.cpp)
target_link_libraries(ColorTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME ColorTests COMMAND ColorTests)

# Intersection Tests
add_executable(IntersectionTests IntersectionTests.cpp)
target_link_libraries(IntersectionTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME IntersectionTests COMMAND IntersectionTests)

# Matrix Tests
add_executable(MatrixTests MatrixTests.cpp)
target_link_libraries(MatrixTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME MatrixTests COMMAND MatrixTests)

# Pattern Tests
add_executable(PatternTests PatternTests.cpp)
target_link_libraries(PatternTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME PatternTests COMMAND PatternTests)

# Plane Tests
add_executable(PlaneTests PlaneTests.cpp)
target_link_libraries(PlaneTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME PlaneTests COMMAND PlaneTests)

# Transformation Tests
add_executable(TransformationTests TransformationTests.cpp)
target_link_libraries(TransformationTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME TransformationTests COMMAND TransformationTests)

# Ray Tests
add_executable(RayTests RayTests.cpp)
target_link_libraries(RayTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME RayTests COMMAND RayTests)

# Sphere Tests
add_executable(SphereTests SphereTests.cpp)
target_link_libraries(SphereTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME SphereTests COMMAND SphereTests)

# Light Tests
add_executable(LightTests LightTests.cpp)
target_link_libraries(LightTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME LightTests COMMAND LightTests)

# World Tests
add_executable(WorldTests WorldTests.cpp)
target_link_libraries(WorldTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME WorldTests COMMAND WorldTests)

# Material Tests
add_executable(MaterialTests MaterialTests.cpp)
target_link_libraries(MaterialTests PRIVATE RayTracerLib gtest gtest_main pthread)
add_test(NAME MaterialTests COMMAND MaterialTests)