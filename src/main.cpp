#include "Tuple.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Sphere.h"
#include "Light.h"
#include "Intersections.h"
#include "World.h"
#include "Camera.h"
#include "Transforms.h"
#include "Ray.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

int main(void)
{
    Sphere floor;
    Transforms floorTransform;
    floorTransform.scale(10, 0.01, 10);
    floor.material.color = Color(1, 0.9, 0.9);
    floor.material.specular = 0;
    floor.setTransform(floorTransform.getTransformMat());

    Sphere leftWall;
    Transforms leftWallTransform;
    leftWallTransform.translate(0, 0, 5)
        .rotateY(M_PI / 4)
        .rotateX(M_PI / 2)
        .scale(10, 0.01, 10);
    leftWall.material = floor.material;
    leftWall.setTransform(leftWallTransform.getTransformMat());

    Sphere rightWall;
    Transforms rightWallTransform;
    rightWallTransform.translate(0, 0, 5)
        .rotateY(-M_PI / 4)
        .rotateX(M_PI / 2)
        .scale(10, 0.01, 10);
    rightWall.material = floor.material;
    rightWall.setTransform(rightWallTransform.getTransformMat());

    Sphere middle;
    Transforms middleTransform;
    middleTransform.translate(-0.5, 1, 0.5);
    middle.material.color = Color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;
    middle.setTransform(middleTransform.getTransformMat());

    Sphere right;
    Transforms rightTransform;
    rightTransform.translate(1.5, 0.5, -0.5)
        .scale(0.5, 0.5, 0.5);
    right.material.color = Color(0.5, 1, 0.1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;
    right.setTransform(rightTransform.getTransformMat());

    Sphere left;
    Transforms leftTransform;
    leftTransform.translate(-1.5, 0.33, -0.75)
        .scale(0.33, 0.33, 0.33);
    left.material.color = Color(1, 0.8, 0.1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;
    left.setTransform(leftTransform.getTransformMat());

    World w = World();
    w.clear();
    w.objects.push_back(std::make_shared<Sphere>(floor));
    w.objects.push_back(std::make_shared<Sphere>(leftWall));
    w.objects.push_back(std::make_shared<Sphere>(rightWall));
    w.objects.push_back(std::make_shared<Sphere>(left));
    w.objects.push_back(std::make_shared<Sphere>(middle));
    w.objects.push_back(std::make_shared<Sphere>(right));
    w.light = Light(Tuple::point(-10, 10, -10), Color(1.0, 1.0, 1.0));

    Camera cam = Camera(200, 100, M_PI / 3);
    cam.transform = Transforms().viewTransform(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));

    Canvas c = cam.render(w);

    Light light = Light(Tuple::point(-10, 10, -10), Color(1.0, 1.0, 1.0));

    std::ofstream ppmFile("sphere.ppm");

    if (ppmFile.is_open())
    {
        std::vector<std::string> ppmContent = c.canvasToPPM();
        for (const auto &line : ppmContent)
        {
            ppmFile << line;
        }
        ppmFile.close();
        std::cout << "PPM file created successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for writing" << std::endl;
    }

    return 0;
};