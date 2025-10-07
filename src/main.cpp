#include "Tuple.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Sphere.h"
#include "Light.h"
#include "Plane.h"
#include "Intersections.h"
#include "World.h"
#include "Camera.h"
#include "Transforms.h"
#include "Ray.h"
#include "Pattern.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

int main(void)
{
    StripePattern stripe = StripePattern(Color(1.0, 0.0, 0.0), Color(0.0, 1.0, 0.0));
    // PerturbedGradientPattern gradient = PerturbedGradientPattern(Color(1.0, 0.0, 0.0), Color(0.0, 1.0, 0.0), 0.8);
    GradientPattern gradient = GradientPattern(Color(1.0, 0.0, 0.0), Color(0.0, 1.0, 0.0));
    // RingPattern ring = RingPattern(Color(1.0, 0.0, 0.0), Color(0.0, 1.0, 0.0));
    // PerturbedRingPattern ring = PerturbedRingPattern(Color(1.0, 0.0, 0.0), Color(0.0, 1.0, 0.0), 0.8);
    PerturbedStripePattern perturbedStripe = PerturbedStripePattern(Color(0.0, 0.7, 0.3), Color(0.0, 0.4, 0.0), 0.5);

    Plane floor;
    floor.material.color = Color(1, 0.9, 0.9);
    // floor.material.pattern = std::make_shared<StripePattern>(stripe);
    floor.material.specular = 0;
    floor.material.reflective = 0.5;

    Sphere middle;
    Transforms middleTransform;
    middleTransform.translate(-0.5, 1, 0.5);
    middle.setTransform(middleTransform.getTransformMat());

    Transforms stripeTransform;
    stripeTransform.rotateY(-M_PI / 4).rotateZ(-M_PI / 4).scale(0.25, 0.25, 0.25);
    perturbedStripe.setTransform(stripeTransform.getTransformMat());
    middle.material.pattern = std::make_shared<PerturbedStripePattern>(perturbedStripe);
    middle.material.color = Color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;
    middle.material.reflective = 0.2;

    Sphere right;
    Transforms rightTransform;
    rightTransform.translate(1.5, 0.5, -0.5)
        .scale(0.5, 0.5, 0.5);
    right.material.color = Color(0.5, 1, 0.1);
    right.material.pattern = std::make_shared<GradientPattern>(gradient);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;
    right.material.transparency = 0.5;
    right.material.refractiveIndex = 1.5;
    right.setTransform(rightTransform.getTransformMat());

    Sphere left;
    Transforms leftTransform;
    leftTransform.translate(-1.5, 0.33, -0.75)
        .scale(0.33, 0.33, 0.33);
    left.material.color = Color(1, 0.8, 0.1);
    right.material.pattern = std::make_shared<StripePattern>(stripe);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;
    left.setTransform(leftTransform.getTransformMat());

    World w = World();
    w.clear();
    w.objects.push_back(std::make_shared<Plane>(floor));
    w.objects.push_back(std::make_shared<Sphere>(left));
    w.objects.push_back(std::make_shared<Sphere>(middle));
    w.objects.push_back(std::make_shared<Sphere>(right));
    w.light = Light(Tuple::point(-10, 10, -10), Color(1.0, 1.0, 1.0));

    // Low res
    // Camera cam = Camera(200, 100, M_PI / 3);

    // High res
    Camera cam = Camera(800, 600, M_PI / 3);
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