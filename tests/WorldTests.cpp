#include <gtest/gtest.h>
#include "Computations.h"
#include "World.h"
#include "Ray.h"
#include "Transforms.h"
#include "Intersections.h"

TEST(WorldTests, WorldCreation)
{
    World w = World();
    EXPECT_EQ(1, 1);
}

TEST(WorldTests, DefaultWorld)
{
    World w = World();
    Transforms t;
    t.scale(0.5, 0.5, 0.5);

    EXPECT_EQ(w.light.position, Tuple::point(-10, 10, -10));
    EXPECT_EQ(w.objects.size(), 2);
    EXPECT_EQ(w.objects[0]->material.color, Color(0.8, 1.0, 0.6));
    EXPECT_NEAR(w.objects[0]->material.diffuse, 0.7, 0.0001);
    EXPECT_NEAR(w.objects[0]->material.specular, 0.2, 0.0001);
    EXPECT_EQ(w.objects[1]->getTransform(), t.getTransformMat());
}

TEST(WorldTests, IntersectWorld)
{
    World w = World();
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Intersections i = w.getIntersections(r);

    EXPECT_EQ(i.xs.size(), 4);
    EXPECT_NEAR(i.xs[0].t, 4, 0.0001);
    EXPECT_NEAR(i.xs[1].t, 4.5, 0.0001);
    EXPECT_NEAR(i.xs[2].t, 5.5, 0.0001);
    EXPECT_NEAR(i.xs[3].t, 6, 0.0001);
}

TEST(WorldTests, ShadingIntersection)
{
    World w = World();
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    auto sPtr = std::dynamic_pointer_cast<Sphere>(w.objects[0]);
    Intersection i(4, sPtr.get());
    Computations comps = Computations(i, r);
    Color c = w.shadeHit(comps);

    EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTests, ShadingIntersectionInside)
{
    World w = World();
    w.light = Light(Tuple::point(0, 0.25, 0), Color(1, 1, 1));
    Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    Sphere s = Sphere();
    s.material = Material();
    Intersection i(0.5, &s);
    Computations comps = Computations(i, r);
    Color c = w.shadeHit(comps);

    EXPECT_EQ(c, Color(0.90498, 0.90498, 0.90498));
}

TEST(WorldTests, ColorAtMiss)
{
    World w = World();
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 1, 0));
    Color c = w.colorAt(r);

    EXPECT_EQ(c, Color(0, 0, 0));
}

TEST(WorldTests, ColorAtHit)
{
    World w = World();
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Color c = w.colorAt(r);

    EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTests, ColorAtIntersectionBehindRay)
{
    World w = World();
    auto outer = std::dynamic_pointer_cast<Sphere>(w.objects[0]);
    outer->material.ambient = 1;
    auto inner = std::dynamic_pointer_cast<Sphere>(w.objects[1]);
    inner->material.ambient = 1;
    Ray r(Tuple::point(0, 0, 0.75), Tuple::vector(0, 0, -1));
    Color c = w.colorAt(r);

    EXPECT_EQ(c, inner->material.color);
}