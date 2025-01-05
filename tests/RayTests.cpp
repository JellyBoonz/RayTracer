#include "Ray.h"
#include "Tuple.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Intersections.h"
#include "Transforms.h"
#include <gtest/gtest.h>

TEST(RayTests, MakeRay)
{
    Tuple o = Tuple::point(1, 2, 3);
    Tuple dir = Tuple::vector(4, 5, 6);
    Ray r(o, dir);

    EXPECT_EQ(r.origin, o);
    EXPECT_EQ(r.direction, dir);
}

TEST(RayTests, ComputePointFromDistance)
{
    Tuple o = Tuple::point(2, 3, 4);
    Tuple dir = Tuple::vector(1, 0, 0);
    Ray r(o, dir);

    EXPECT_EQ(r.position(0), Tuple::point(2, 3, 4));
    EXPECT_EQ(r.position(1), Tuple::point(3, 3, 4));
    EXPECT_EQ(r.position(-1), Tuple::point(1, 3, 4));
    EXPECT_EQ(r.position(2.5), Tuple::point(4.5, 3, 4));
}

TEST(RayTests, SphereIntersection)
{
    Tuple o = Tuple::point(0, 0, -5);
    Tuple dir = Tuple::vector(0, 0, 1);
    Ray r(o, dir);
    Sphere s;

    std::vector<Intersection> xs = r.intersect(&s);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4.0);
    EXPECT_EQ(xs[1].t, 6.0);
}

TEST(RayTests, RayInSphereIntersection)
{
    Tuple o = Tuple::point(0, 0, 0);
    Tuple dir = Tuple::vector(0, 0, 1);
    Ray r(o, dir);
    Sphere s;

    std::vector<Intersection> xs = r.intersect(&s);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, -1.0);
    EXPECT_EQ(xs[1].t, 1.0);
    EXPECT_EQ(xs[0].object, &s);
}

TEST(RayTests, IntersectionObjectInstantiation)
{
    Sphere s;
    Intersection i(3.5, &s);

    EXPECT_EQ(i.t, 3.5);
    EXPECT_EQ(i.object, &s);
}

TEST(RayTests, IntersectionAggregation)
{
    Sphere s;
    Intersection i1(1.0, &s);
    Intersection i2(2.0, &s);
    Intersections i({i1, i2});

    EXPECT_EQ(i.xs[0].t, 1.0);
    EXPECT_EQ(i.xs[1].t, 2.0);
}

TEST(RayTests, TestHit)
{
    Sphere s;
    Intersection i1(1.0, &s);
    Intersection i2(2.0, &s);
    Intersections i({i1, i2});

    Intersection i3 = i.hit();
    EXPECT_EQ(i3.t, i1.t);
    EXPECT_EQ(i3.object, i1.object);
}

TEST(RayTests, TestHitWithNegativeT)
{
    Sphere s;
    Intersection i1(-1.0, &s);
    Intersection i2(1.0, &s);
    Intersections xs({i1, i2});

    Intersection i = xs.hit();
    EXPECT_EQ(i.t, i2.t);
    EXPECT_EQ(i.object, i2.object);
}

TEST(IntersectionsTests, HitAllNegatives)
{
    Sphere s;
    Intersection i1(-1.0, &s);
    Intersection i2(-2.0, &s);

    Intersections intersections({i1, i2});

    Intersection result = intersections.hit();

    EXPECT_EQ(result.t, std::numeric_limits<double>::infinity());
    EXPECT_EQ(result.object, nullptr);
}

TEST(RayTests, TestHitWithLowestNonNegativeT)
{
    Sphere s;
    Intersection i1(5.0, &s);
    Intersection i2(7.0, &s);
    Intersection i3(-3.0, &s);
    Intersection i4(2.0, &s);
    Intersections xs({i1, i2, i3, i4});

    Intersection i = xs.hit();
    EXPECT_EQ(i.t, i4.t);
    EXPECT_EQ(i.object, i4.object);
}

TEST(RayTests, TranslatingARay)
{
    Ray r(Tuple::point(1, 2, 3), Tuple::vector(0, 1, 0));
    Transforms t;
    t.translate(3, 4, 5);
    Ray r2 = t.applyTo(r);

    EXPECT_EQ(r2.origin, Tuple::point(4, 6, 8));
    EXPECT_EQ(r2.direction, Tuple::vector(0, 1, 0));
}

TEST(RayTests, ScalingARay)
{
    Ray r(Tuple::point(1, 2, 3), Tuple::vector(0, 1, 0));
    Transforms t;
    t.scale(2, 3, 4);
    Ray r2 = t.applyTo(r);

    EXPECT_EQ(r2.origin, Tuple::point(2, 6, 12));
    EXPECT_EQ(r2.direction, Tuple::vector(0, 3, 0));
}

TEST(RayTests, TransformRayBeforeIntersection)
{
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Transforms t;
    Sphere s;

    t.scale(2, 2, 2);
    s.setTransform(t.getTransformMat());
    Intersections i = r.intersect(&s);

    EXPECT_EQ(i.xs.size(), 2);
    EXPECT_EQ(i.xs[0].t, 3);
    EXPECT_EQ(i.xs[1].t, 7);
}