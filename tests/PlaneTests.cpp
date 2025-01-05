#include <gtest/gtest.h>
#include "Plane.h"
#include "Transforms.h"
#include "Tuple.h"
#include "Ray.h"

TEST(PlaneTests, NormalIsConstantEverywhere)
{
    Plane p = Plane();
    Tuple n1 = p.normalAt(Tuple::point(0, 0, 0));
    Tuple n2 = p.normalAt(Tuple::point(10, 0, -10));
    Tuple n3 = p.normalAt(Tuple::point(-5, 0, 150));
    Tuple expected = Tuple::vector(0, 1, 0);
    EXPECT_EQ(n1, expected);
    EXPECT_EQ(n2, expected);
    EXPECT_EQ(n3, expected);
}

TEST(PlaneTests, IntersectWithRayParallelToPlane)
{
    Plane p = Plane();
    Ray r(Tuple::point(0, 10, 0), Tuple::vector(0, 0, 1));
    Intersections i = r.intersect(&p);
    EXPECT_EQ(i.xs.size(), 0);
}

TEST(PlaneTests, IntersectWithCoplanarRay)
{
    Plane p = Plane();
    Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    Intersections i = r.intersect(&p);
    EXPECT_EQ(i.xs.size(), 0);
}

TEST(PlaneTests, RayIntersectingPlaneFromAbove)
{
    Plane p = Plane();
    Ray r(Tuple::point(0, 1, 0), Tuple::vector(0, -1, 0));
    Intersections i = r.intersect(&p);
    EXPECT_EQ(i.xs.size(), 1);
    EXPECT_EQ(i.xs[0].t, 1);
    EXPECT_EQ(i.xs[0].object, &p);
}

TEST(PlaneTests, RayIntersectingPlaneFromBelow)
{
    Plane p = Plane();
    Ray r(Tuple::point(0, -1, 0), Tuple::vector(0, 1, 0));
    Intersections i = r.intersect(&p);
    EXPECT_EQ(i.xs.size(), 1);
    EXPECT_EQ(i.xs[0].t, 1);
    EXPECT_EQ(i.xs[0].object, &p);
}