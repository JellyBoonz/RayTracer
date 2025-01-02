#include <gtest/gtest.h>
#include "Camera.h"
#include "Canvas.h"
#include "Ray.h"
#include "Transforms.h"

TEST(CameraTests, CameraCreation)
{
    Camera c = Camera(160, 120, M_PI / 2);
    EXPECT_EQ(c.hsize, 160);
    EXPECT_EQ(c.vsize, 120);
    EXPECT_NEAR(c.field_of_view, M_PI / 2, 0.0001);
    EXPECT_EQ(c.transform, Matrix::ID_MAT);
}

TEST(CameraTests, RayThroughCenterOfCanvas)
{
    Camera c = Camera(201, 101, M_PI / 2);
    Ray r = c.rayForPixel(100, 50);
    EXPECT_EQ(r.origin, Tuple::point(0, 0, 0));
    EXPECT_EQ(r.direction, Tuple::vector(0, 0, -1));
}

TEST(CameraTests, RayThroughCornerOfCanvas)
{
    Camera c = Camera(201, 101, M_PI / 2);
    Ray r = c.rayForPixel(0, 0);
    EXPECT_EQ(r.origin, Tuple::point(0, 0, 0));
    EXPECT_EQ(r.direction, Tuple::vector(0.66519, 0.33259, -0.66851));
}

TEST(CameraTests, RayWhenCameraIsTransformed)
{
    Camera c = Camera(201, 101, M_PI / 2);
    Transforms t;
    t.rotateY(M_PI / 4).translate(0, -2, 5);
    c.transform = t.getTransformMat();
    Ray r = c.rayForPixel(100, 50);
    EXPECT_EQ(r.origin, Tuple::point(0, 2, -5));
    EXPECT_EQ(r.direction, Tuple::vector(sqrt(2) / 2, 0, -sqrt(2) / 2));
}

TEST(CameraTests, RenderWorld)
{
    World w = World();
    Camera c = Camera(11, 11, M_PI / 2);
    Tuple from = Tuple::point(0, 0, -5);
    Tuple to = Tuple::point(0, 0, 0);
    Tuple up = Tuple::vector(0, 1, 0);
    c.transform = Transforms().viewTransform(from, to, up);
    Canvas image = c.render(w);
    EXPECT_EQ(image.pixelAt(5, 5), Color(0.38066, 0.47583, 0.2855));
}