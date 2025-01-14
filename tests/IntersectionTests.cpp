#include <gtest/gtest.h>
#include "Computations.h"
#include "Intersection.h"
#include "Sphere.h"
#include "Ray.h"

TEST(IntersectionTests, PreComputingStateOfIntersection)
{
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere s = Sphere();
    Intersection i(4, &s);
    Computations comps = Computations(i, r);

    EXPECT_NEAR(comps.t, i.t, 0.0001);
    EXPECT_EQ(comps.object, i.object);
    EXPECT_EQ(comps.point, Tuple::point(0, 0, -1));
    EXPECT_EQ(comps.eyev, Tuple::vector(0, 0, -1));
    EXPECT_EQ(comps.normalv, Tuple::vector(0, 0, -1));
}

TEST(IntersectionTests, HitWhenIntersectionOccursOnOutside)
{
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere s = Sphere();
    Intersection i(4, &s);
    Computations comps = Computations(i, r);

    EXPECT_FALSE(comps.inside);
}

TEST(IntersectionTests, TheHitShouldOffsetThePoint)
{
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere s = Sphere();
    Transforms t;
    t.translate(0, 0, 1);
    s.setTransform(t.getTransformMat());

    Intersection i(5, &s);
    Computations comps = Computations(i, r);

    EXPECT_LT(comps.overPoint.z, -EPSILON / 2);
    EXPECT_GT(comps.point.z, comps.overPoint.z);
}