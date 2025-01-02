#ifndef CAMERA_H
#define CAMERA_H

#include "Tuple.h"
#include "Matrix.h"
#include "Ray.h"
#include "World.h"
#include "Canvas.h"

class Camera
{
public:
    int hsize;
    int vsize;
    float field_of_view;
    float half_width, half_height;
    Matrix transform = Matrix::ID_MAT;
    float pixel_size;

    Camera(int hsize, int vsize, float field_of_view) : hsize(hsize), vsize(vsize), field_of_view(field_of_view)
    {
        float half_view = tan(field_of_view / 2);
        float aspect = (float)hsize / vsize;
        if (aspect >= 1)
        {
            half_width = half_view;
            half_height = half_view / aspect;
        }
        else
        {
            half_width = half_view * aspect;
            half_height = half_view;
        }
        pixel_size = (half_width * 2) / hsize;
    }

    Ray rayForPixel(int px, int py)
    {
        float xoffset = (px + 0.5) * pixel_size;
        float yoffset = (py + 0.5) * pixel_size;
        float world_x = half_width - xoffset;
        float world_y = half_height - yoffset;

        // Transform the canvas point and camera origin to world space
        Tuple pixel = transform.inverse() * Tuple::point(world_x, world_y, -1);
        Tuple origin = transform.inverse() * Tuple::point(0, 0, 0);

        // The vector from the camera origin through the canvas point
        Tuple direction = (pixel - origin).normalize();
        return Ray(origin, direction);
    }

    Canvas render(World &world)
    {
        Canvas image(hsize, vsize);
        for (int y = 0; y < vsize; y++)
        {
            for (int x = 0; x < hsize; x++)
            {
                Ray ray = rayForPixel(x, y);
                Color color = world.colorAt(ray);
                image.writePixel(x, y, color);
            }
        }
        return image;
    }
};
#endif