#include "Material.h"
#include "Plane.h"
#include "Ray.h"
#include "Computations.h"
#include "World.h"
#include <gtest/gtest.h>

TEST(MaterialTests, ReflectiveDefault)
{
    Material m;
    EXPECT_EQ(m.reflective, 0.0);
}

TEST(MaterialTests, PrecomputingReflectionVector)
{
    Plane p;
    Ray r(Tuple::point(0, 1, -1), Tuple::vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    Intersection i(sqrt(2), &p);
    Computations comps(i, r);
    EXPECT_EQ(comps.reflectv, Tuple::vector(0, sqrt(2) / 2, sqrt(2) / 2));
}

TEST(MaterialTests, NonReflectiveMaterial)
{
    World w;
    Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    Sphere s = w.objects[1] ? *std::dynamic_pointer_cast<Sphere>(w.objects[1]) : Sphere();
    s.material.ambient = 1.0;
    Intersection i(1, &s);
    Computations comps(i, r);
    Color c = w.reflectedColor(comps);
    EXPECT_EQ(c, Color(0.0, 0.0, 0.0));
}

TEST(MaterialTests, ReflectiveMaterial)
{
    World w;
    auto p = std::make_shared<Plane>();
    p->setTransform(Transforms().translate(0, -1, 0).getTransformMat());
    p->material.reflective = 0.5;
    w.objects.push_back(p);

    Ray r(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    Intersection i(sqrt(2), p.get());
    Computations comps(i, r);
    Color c = w.reflectedColor(comps);
    EXPECT_EQ(c, Color(0.190503, 0.238129, 0.142877));
}

TEST(MaterialTests, ReflectiveMaterialWithShadeHit)
{
    World w;
    auto p = std::make_shared<Plane>();
    p->setTransform(Transforms().translate(0, -1, 0).getTransformMat());
    p->material.reflective = 0.5;
    w.objects.push_back(p);

    Ray r(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    Intersection i(sqrt(2), p.get());
    Computations comps(i, r);
    Color c = w.shadeHit(comps);
    EXPECT_EQ(c, Color(0.876928, 0.924554, 0.829303));
}