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

# Tuple Tests
add_executable(TupleTests TupleTests.cpp ../src/Tuple.cpp)
target_link_libraries(TupleTests PRIVATE gtest gtest_main pthread)
add_test(NAME TupleTests COMMAND TupleTests)

# Canvas Tests
add_executable(CanvasTests CanvasTests.cpp ../src/Tuple.cpp)
target_link_libraries(CanvasTests PRIVATE gtest gtest_main pthread)
add_test(NAME CanvasTests COMMAND CanvasTests)

# Camera Tests
add_executable(CameraTests CameraTests.cpp ../src/Tuple.cpp ../src/Matrix.cpp ../src/Ray.cpp ../src/Sphere.cpp ../src/Transforms.cpp ../src/World.cpp ../src/Light.cpp)
target_link_libraries(CameraTests PRIVATE gtest gtest_main pthread)
add_test(NAME CameraTests COMMAND CameraTests)

# Color Tests
add_executable(ColorTests ColorTests.cpp ../src/Tuple.cpp)
target_link_libraries(ColorTests PRIVATE gtest gtest_main pthread)
add_test(NAME ColorTests COMMAND ColorTests)

# Intersection Tests
add_executable(IntersectionTests IntersectionTests.cpp ../src/Computations.h ../src/Intersection.h ../src/Tuple.cpp ../src/Matrix.cpp ../src/Ray.cpp ../src/Sphere.cpp ../src/Transforms.cpp)
target_link_libraries(IntersectionTests PRIVATE gtest gtest_main pthread)
add_test(NAME IntersectionTests COMMAND IntersectionTests)

# Matrix Tests
add_executable(MatrixTests MatrixTests.cpp ../src/Matrix.cpp ../src/Tuple.cpp)
target_link_libraries(MatrixTests PRIVATE gtest gtest_main pthread)
add_test(NAME MatrixTests COMMAND MatrixTests)

# Transformation Tests
add_executable(TransformationTests TransformationTests.cpp ../src/Ray.cpp ../src/Sphere.cpp ../src/Transforms.cpp ../src/Matrix.cpp ../src/Tuple.cpp ../src/World.cpp ../src/Light.cpp)
target_link_libraries(TransformationTests PRIVATE gtest gtest_main pthread)
add_test(NAME TransformationTests COMMAND TransformationTests)

# Ray Tests
add_executable(RayTests RayTests.cpp ../src/Transforms.cpp ../src/Matrix.cpp ../src/Light.cpp ../src/Tuple.cpp ../src/Ray.cpp ../src/Sphere.cpp ../src/World.cpp)
target_link_libraries(RayTests PRIVATE gtest gtest_main pthread)
add_test(NAME RayTests COMMAND RayTests)

# Sphere Tests
add_executable(SphereTests SphereTests.cpp ../src/Transforms.cpp ../src/Matrix.cpp ../src/World.cpp ../src/Light.cpp ../src/Tuple.cpp ../src/Ray.cpp ../src/Sphere.cpp)
target_link_libraries(SphereTests PRIVATE gtest gtest_main pthread)
add_test(NAME SphereTests COMMAND SphereTests)

# Light Tests
add_executable(LightTests LightTests.cpp ../src/Transforms.cpp ../src/Matrix.cpp ../src/Ray.cpp ../src/Tuple.cpp ../src/Light.cpp ../src/Sphere.cpp ../src/World.cpp)
target_link_libraries(LightTests PRIVATE gtest gtest_main pthread)
add_test(NAME LightTests COMMAND LightTests)

# World Tests
add_executable(WorldTests WorldTests.cpp ../src/Intersectable.h ../src/Computations.h ../src/Transforms.cpp ../src/Matrix.cpp ../src/Ray.cpp ../src/Tuple.cpp ../src/Light.cpp ../src/Sphere.cpp ../src/World.cpp)
target_link_libraries(WorldTests PRIVATE gtest gtest_main pthread)
add_test(NAME WorldTests COMMAND WorldTests)