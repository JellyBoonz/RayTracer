#include "Tuple.h"
#include <gtest/gtest.h>

TEST(TupleTests, CreatePoint)
{
    Tuple point = Tuple::point(1.0, 2.0, 3.0);
    EXPECT_TRUE(point.isPoint());
    EXPECT_FALSE(point.isVector());
    EXPECT_EQ(point.x, 1.0);
    EXPECT_EQ(point.y, 2.0);
    EXPECT_EQ(point.z, 3.0);
}

TEST(TupleTests, CreateVector)
{
    Tuple vector = Tuple::vector(1.0, 2.0, 3.0);
    EXPECT_FALSE(vector.isPoint());
    EXPECT_TRUE(vector.isVector());
    EXPECT_EQ(vector.x, 1.0);
    EXPECT_EQ(vector.y, 2.0);
    EXPECT_EQ(vector.z, 3.0);
}

TEST(TupleTests, CreateTuplePoint)
{
    Tuple tuple = Tuple(1.0, 2.0, 3.0, 1.0);
    EXPECT_TRUE(tuple.isPoint());
    EXPECT_FALSE(tuple.isVector());
}

TEST(TupleTests, CreateTupleVector)
{
    Tuple tuple = Tuple(1.0, 2.0, 3.0, 0.0);
    EXPECT_FALSE(tuple.isPoint());
    EXPECT_TRUE(tuple.isVector());
}

TEST(TupleTests, AddTuples)
{
    Tuple tuple1 = Tuple(-1.0, 1.0, -5.0, 1.0);
    Tuple tuple2 = Tuple(1.0, 2.0, 3.0, 0.0);

    Tuple tuple3 = tuple1 + tuple2;

    EXPECT_EQ(tuple3, Tuple(0.0, 3.0, -2.0, 1.0));
}

TEST(TupleTests, SubtractTuples)
{
    Tuple tuple1 = Tuple(-1.0, 1.0, -5.0, 1.0);
    Tuple tuple2 = Tuple(1.0, 2.0, 3.0, 0.0);

    Tuple tuple3 = tuple1 - tuple2;

    EXPECT_EQ(tuple3, Tuple(-2.0, -1.0, -8.0, 1.0));
}

TEST(TupleTests, SubtractPoints)
{
    Tuple point1 = Tuple::point(-1.0, 2.0, 3.0);
    Tuple point2 = Tuple::point(4.0, -1.0, 3.0);

    Tuple vector = point1 - point2;

    EXPECT_EQ(vector, Tuple(-5.0, 3.0, 0.0, 0.0));
    EXPECT_TRUE(vector.isVector());
    EXPECT_FALSE(vector.isPoint());
}

TEST(TupleTests, SubtractVectorFromPoint)
{
    Tuple vector = Tuple::vector(-1.0, 2.0, 3.0);
    Tuple point = Tuple::point(4.0, -1.0, 3.0);

    Tuple point2 = point - vector;

    EXPECT_EQ(point2, Tuple(5.0, -3.0, 0.0, 1.0));
    EXPECT_FALSE(point2.isVector());
    EXPECT_TRUE(point2.isPoint());
}

TEST(TupleTests, SubtractVectors)
{
    Tuple vector1 = Tuple::vector(-1.0, 2.0, 3.0);
    Tuple vector2 = Tuple::vector(4.0, -1.0, 3.0);

    Tuple vector3 = vector1 - vector2;

    EXPECT_EQ(vector3, Tuple(-5.0, 3.0, 0.0, 0.0));
    EXPECT_TRUE(vector3.isVector());
    EXPECT_FALSE(vector3.isPoint());
}

TEST(TupleTests, NegateTuple)
{
    Tuple tuple = Tuple(-1.0, 3.0, 9.0, 0.0);

    Tuple newTuple = -tuple;

    EXPECT_EQ(newTuple, Tuple(1.0, -3.0, -9.0, 0.0));
}

TEST(TupleTests, ScalerMultiply)
{
    Tuple vector = Tuple::vector(1.0, 2.0, 3.0);

    Tuple scaledVector = vector * 2.0;

    EXPECT_EQ(scaledVector, Tuple(2.0, 4.0, 6.0, 0.0));
}

TEST(TupleTests, ScalerDivide)
{
    Tuple vector = Tuple::vector(1.0, 2.0, 3.0);

    Tuple scaledVector = vector / 2.0;

    EXPECT_EQ(scaledVector, Tuple(0.5, 1.0, 1.5, 0.0));
}

TEST(TupleTests, Magnitude)
{
    Tuple vector = Tuple::vector(1.0, 2.0, 3.0);

    double mag = vector.magnitude();

    EXPECT_EQ(mag, sqrt(14));
}

TEST(TupleTests, Normalize)
{
    Tuple vector = Tuple::vector(1.0, 2.0, 3.0);

    double length = vector.normalize().magnitude();

    EXPECT_EQ(length, 1.0);
}

TEST(TupleTests, DotProduct)
{
    Tuple vector1 = Tuple::vector(1.0, 2.0, 3.0);
    Tuple vector2 = Tuple::vector(2.0, 3.0, 4.0);

    double dotProd = vector1.dot(vector2);

    EXPECT_EQ(dotProd, 20.0);
}

TEST(TupleTests, CrossProduct)
{
    Tuple vector1 = Tuple::vector(1.0, 2.0, 3.0);
    Tuple vector2 = Tuple::vector(2.0, 3.0, 4.0);

    Tuple vector3 = vector1.cross(vector2);

    EXPECT_EQ(vector3, Tuple(-1.0, 2.0, -1.0, 0.0));
}

TEST(TupleTests, ReflectVector)
{
    Tuple vector = Tuple::vector(1.0, -1.0, 0.0);
    Tuple normal = Tuple::vector(0.0, 1.0, 0.0);

    Tuple reflected = vector.reflect(normal);

    EXPECT_EQ(reflected, Tuple(1.0, 1.0, 0.0, 0.0));
}