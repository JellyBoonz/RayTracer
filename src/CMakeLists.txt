# Collect source files
set(SOURCES
    RayTracer.cpp
    Light.cpp
    Tuple.cpp
    Matrix.cpp
    Transforms.cpp
    Camera.h
    Ray.cpp
    Sphere.cpp
    main.cpp
    World.cpp
)

# Create an executable for the ray tracer
add_executable(ray_tracer ${SOURCES})
