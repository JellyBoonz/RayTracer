# Collect source files
set(SOURCES
    RayTracer.cpp
    Light.cpp
    Tuple.cpp
    Matrix.cpp
    Plane.h
    Pattern.cpp
    Noise.cpp
    Transforms.cpp
    Camera.h
    Ray.cpp
    Sphere.cpp
    main.cpp
    World.cpp
)

# Create an executable for the ray tracer
add_executable(ray_tracer ${SOURCES})

# Link threading library
target_link_libraries(ray_tracer Threads::Threads)
