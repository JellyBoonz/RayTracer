# Ray Tracer

A C++ ray tracer implementation with comprehensive test suite.

## Building the Project

### Prerequisites
- CMake 3.10 or higher
- C++17 compatible compiler
- Make (or Ninja)

### Build Instructions

1. **Create and navigate to build directory:**
   ```bash
   mkdir build
   cd build
   ```

2. **Configure with CMake:**
   ```bash
   cmake ..
   ```

3. **Build everything:**
   ```bash
   make
   ```

## Running Tests

### Run All Tests
```bash
cd build
ctest
```

### Run Tests with Verbose Output
```bash
cd build
ctest --verbose
```

### Run Specific Test
```bash
cd build
ctest -R TupleTests
ctest -R CanvasTests
ctest -R CameraTests
# ... or any other test name
```

### Run Test Executable Directly
```bash
cd build
./tests/TupleTests
./tests/CanvasTests
./tests/CameraTests
# ... or any other test executable
```

### Build Only Tests
```bash
cd build
make tests
```

## Running the Main Program

### Build the Ray Tracer
```bash
cd build
make ray_tracer
```

### Run the Ray Tracer
```bash
cd build
./src/ray_tracer
```

## Available Test Suites

- `TupleTests` - Tuple operations and transformations
- `CanvasTests` - Canvas rendering and PPM output
- `CameraTests` - Camera functionality and ray generation
- `ColorTests` - Color operations and blending
- `IntersectionTests` - Ray-object intersection calculations
- `MatrixTests` - Matrix operations and transformations
- `PatternTests` - Material patterns and textures
- `PlaneTests` - Plane geometry and intersections
- `RayTests` - Ray operations and transformations
- `SphereTests` - Sphere geometry and intersections
- `TransformationTests` - Object transformations
- `LightTests` - Lighting calculations and shading
- `WorldTests` - Scene composition and rendering

## Quick Commands

```bash
# Build everything
make

# Run all tests
ctest

# Build and run ray tracer
make ray_tracer && ./src/ray_tracer

# Build specific test
make TupleTests

# Run specific test
./tests/TupleTests
```