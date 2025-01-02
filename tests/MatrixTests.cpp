#include "Matrix.h"
#include "Tuple.h"
#include <gtest/gtest.h>

TEST(MatrixTests, ConstructMatrix)
{
    Matrix mat = Matrix();

    mat.add(0, 0, 1.0);
    mat.add(0, 1, 2.0);
    mat.add(0, 2, 3.0);
    mat.add(0, 3, 4.0);
    mat.add(1, 0, 5.5);
    mat.add(1, 1, 6.5);
    mat.add(1, 2, 7.5);
    mat.add(1, 3, 8.5);
    mat.add(2, 0, 9.0);
    mat.add(2, 1, 10.0);
    mat.add(2, 2, 11.0);
    mat.add(2, 3, 12.0);
    mat.add(3, 0, 13.5);
    mat.add(3, 1, 14.5);
    mat.add(3, 2, 15.5);
    mat.add(3, 3, 16.5);

    EXPECT_DOUBLE_EQ(mat.at(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(mat.at(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(mat.at(0, 2), 3.0);
    EXPECT_DOUBLE_EQ(mat.at(0, 3), 4.0);
    EXPECT_DOUBLE_EQ(mat.at(1, 0), 5.5);
    EXPECT_DOUBLE_EQ(mat.at(1, 1), 6.5);
    EXPECT_DOUBLE_EQ(mat.at(1, 2), 7.5);
    EXPECT_DOUBLE_EQ(mat.at(1, 3), 8.5);
    EXPECT_DOUBLE_EQ(mat.at(2, 0), 9.0);
    EXPECT_DOUBLE_EQ(mat.at(2, 1), 10.0);
    EXPECT_DOUBLE_EQ(mat.at(2, 2), 11.0);
    EXPECT_DOUBLE_EQ(mat.at(2, 3), 12.0);
    EXPECT_DOUBLE_EQ(mat.at(3, 0), 13.5);
    EXPECT_DOUBLE_EQ(mat.at(3, 1), 14.5);
    EXPECT_DOUBLE_EQ(mat.at(3, 2), 15.5);
    EXPECT_DOUBLE_EQ(mat.at(3, 3), 16.5);
}

TEST(MatrixTests, ConstructMatrix3x3)
{
    Matrix mat = Matrix(3, 3, 0.0);

    mat.add(0, 0, 1.0);
    mat.add(0, 1, 2.0);
    mat.add(0, 2, 3.0);
    mat.add(1, 0, 5.5);
    mat.add(1, 1, 6.5);
    mat.add(1, 2, 7.5);
    mat.add(2, 0, 9.0);
    mat.add(2, 1, 10.0);
    mat.add(2, 2, 11.0);

    EXPECT_DOUBLE_EQ(mat.at(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(mat.at(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(mat.at(0, 2), 3.0);
    EXPECT_DOUBLE_EQ(mat.at(1, 0), 5.5);
    EXPECT_DOUBLE_EQ(mat.at(1, 1), 6.5);
    EXPECT_DOUBLE_EQ(mat.at(1, 2), 7.5);
    EXPECT_DOUBLE_EQ(mat.at(2, 0), 9.0);
    EXPECT_DOUBLE_EQ(mat.at(2, 1), 10.0);
    EXPECT_DOUBLE_EQ(mat.at(2, 2), 11.0);
}

TEST(MatrixTests, ConstructMatrix2X2)
{
    Matrix mat = Matrix(2, 2, 0.0);

    mat.add(0, 0, -3.0);
    mat.add(0, 1, -5.0);
    mat.add(1, 0, 1.0);
    mat.add(1, 1, -2.0);

    EXPECT_DOUBLE_EQ(mat.at(0, 0), -3.0);
    EXPECT_DOUBLE_EQ(mat.at(0, 1), -5.0);
    EXPECT_DOUBLE_EQ(mat.at(1, 0), 1.0);
    EXPECT_DOUBLE_EQ(mat.at(1, 1), -2.0);
}

TEST(MatrixTests, EqualityOperator)
{
    // Create and populate the first matrix
    Matrix mat1;
    mat1.add(0, 0, 1.0);
    mat1.add(0, 1, 2.0);
    mat1.add(0, 2, 3.0);
    mat1.add(0, 3, 4.0);
    mat1.add(1, 0, 5.5);
    mat1.add(1, 1, 6.5);
    mat1.add(1, 2, 7.5);
    mat1.add(1, 3, 8.5);
    mat1.add(2, 0, 9.0);
    mat1.add(2, 1, 10.0);
    mat1.add(2, 2, 11.0);
    mat1.add(2, 3, 12.0);
    mat1.add(3, 0, 13.5);
    mat1.add(3, 1, 14.5);
    mat1.add(3, 2, 15.5);
    mat1.add(3, 3, 16.5);

    // Create and populate the second matrix with identical values
    Matrix mat2;
    mat2.add(0, 0, 1.0);
    mat2.add(0, 1, 2.0);
    mat2.add(0, 2, 3.0);
    mat2.add(0, 3, 4.0);
    mat2.add(1, 0, 5.5);
    mat2.add(1, 1, 6.5);
    mat2.add(1, 2, 7.5);
    mat2.add(1, 3, 8.5);
    mat2.add(2, 0, 9.0);
    mat2.add(2, 1, 10.0);
    mat2.add(2, 2, 11.0);
    mat2.add(2, 3, 12.0);
    mat2.add(3, 0, 13.5);
    mat2.add(3, 1, 14.5);
    mat2.add(3, 2, 15.5);
    mat2.add(3, 3, 16.5);

    // Create and populate a third matrix with different values
    Matrix mat3;
    mat3.add(0, 0, 1.1); // Slightly different value
    mat3.add(0, 1, 2.0);
    mat3.add(0, 2, 3.0);
    mat3.add(0, 3, 4.0);
    mat3.add(1, 0, 5.5);
    mat3.add(1, 1, 6.5);
    mat3.add(1, 2, 7.5);
    mat3.add(1, 3, 8.5);
    mat3.add(2, 0, 9.0);
    mat3.add(2, 1, 10.0);
    mat3.add(2, 2, 11.0);
    mat3.add(2, 3, 12.0);
    mat3.add(3, 0, 13.5);
    mat3.add(3, 1, 14.5);
    mat3.add(3, 2, 15.5);
    mat3.add(3, 3, 16.5);

    // Test for equality
    EXPECT_TRUE(mat1 == mat2) << "mat1 and mat2 should be equal";
    EXPECT_FALSE(mat1 == mat3) << "mat1 and mat3 should not be equal";
}

TEST(MatrixTests, MatrixMultiply)
{
    // Define two 4x4 matrices
    Matrix mat1;
    mat1.add(0, 0, 1.0);
    mat1.add(0, 1, 2.0);
    mat1.add(0, 2, 3.0);
    mat1.add(0, 3, 4.0);
    mat1.add(1, 0, 5.0);
    mat1.add(1, 1, 6.0);
    mat1.add(1, 2, 7.0);
    mat1.add(1, 3, 8.0);
    mat1.add(2, 0, 9.0);
    mat1.add(2, 1, 10.0);
    mat1.add(2, 2, 11.0);
    mat1.add(2, 3, 12.0);
    mat1.add(3, 0, 13.0);
    mat1.add(3, 1, 14.0);
    mat1.add(3, 2, 15.0);
    mat1.add(3, 3, 16.0);

    Matrix mat2;
    mat2.add(0, 0, 17.0);
    mat2.add(0, 1, 18.0);
    mat2.add(0, 2, 19.0);
    mat2.add(0, 3, 20.0);
    mat2.add(1, 0, 21.0);
    mat2.add(1, 1, 22.0);
    mat2.add(1, 2, 23.0);
    mat2.add(1, 3, 24.0);
    mat2.add(2, 0, 25.0);
    mat2.add(2, 1, 26.0);
    mat2.add(2, 2, 27.0);
    mat2.add(2, 3, 28.0);
    mat2.add(3, 0, 29.0);
    mat2.add(3, 1, 30.0);
    mat2.add(3, 2, 31.0);
    mat2.add(3, 3, 32.0);

    // Expected result of mat1 * mat2
    Matrix expected;
    expected.add(0, 0, 250.0);
    expected.add(0, 1, 260.0);
    expected.add(0, 2, 270.0);
    expected.add(0, 3, 280.0);
    expected.add(1, 0, 618.0);
    expected.add(1, 1, 644.0);
    expected.add(1, 2, 670.0);
    expected.add(1, 3, 696.0);
    expected.add(2, 0, 986.0);
    expected.add(2, 1, 1028.0);
    expected.add(2, 2, 1070.0);
    expected.add(2, 3, 1112.0);
    expected.add(3, 0, 1354.0);
    expected.add(3, 1, 1412.0);
    expected.add(3, 2, 1470.0);
    expected.add(3, 3, 1528.0);

    // Perform matrix multiplication
    Matrix result = mat1 * mat2;

    // Verify the result matches the expected matrix
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            EXPECT_DOUBLE_EQ(result.at(i, j), expected.at(i, j)) << "Mismatch at element (" << i << ", " << j << ")";
        }
    }
}

TEST(MatrixTests, MatrixTupleMultiply)
{
    Matrix mat1;
    mat1.add(0, 0, 1.0);
    mat1.add(0, 1, 2.0);
    mat1.add(0, 2, 3.0);
    mat1.add(0, 3, 4.0);
    mat1.add(1, 0, 5.5);
    mat1.add(1, 1, 6.5);
    mat1.add(1, 2, 7.5);
    mat1.add(1, 3, 8.5);
    mat1.add(2, 0, 9.0);
    mat1.add(2, 1, 10.0);
    mat1.add(2, 2, 11.0);
    mat1.add(2, 3, 12.0);
    mat1.add(3, 0, 13.5);
    mat1.add(3, 1, 14.5);
    mat1.add(3, 2, 15.5);
    mat1.add(3, 3, 16.5);

    Tuple tup = Tuple(1.0, 2.0, 3.0, 4.0);

    Tuple expected(
        30.0,
        75.0,
        110.0,
        155.0);

    Tuple result = mat1 * tup;

    EXPECT_DOUBLE_EQ(result.x, expected.x);
    EXPECT_DOUBLE_EQ(result.y, expected.y);
    EXPECT_DOUBLE_EQ(result.z, expected.z);
    EXPECT_DOUBLE_EQ(result.w, expected.w);
}

TEST(MatrixTest, IdentityMultiplication)
{
    Matrix testMatrix(4, 4, 0.0);
    testMatrix.add(0, 0, 1.0);
    testMatrix.add(0, 1, 2.0);
    testMatrix.add(0, 2, 3.0);
    testMatrix.add(0, 3, 4.0);
    testMatrix.add(1, 0, 5.0);
    testMatrix.add(1, 1, 6.0);
    testMatrix.add(1, 2, 7.0);
    testMatrix.add(1, 3, 8.0);
    testMatrix.add(2, 0, 9.0);
    testMatrix.add(2, 1, 10.0);
    testMatrix.add(2, 2, 11.0);
    testMatrix.add(2, 3, 12.0);
    testMatrix.add(3, 0, 13.0);
    testMatrix.add(3, 1, 14.0);
    testMatrix.add(3, 2, 15.0);
    testMatrix.add(3, 3, 16.0);

    Matrix leftResult = testMatrix * Matrix::ID_MAT;
    EXPECT_EQ(leftResult, testMatrix);

    Matrix rightResult = Matrix::ID_MAT * testMatrix;
    EXPECT_EQ(rightResult, testMatrix);
}

TEST(MatrixTest, TwoByTwoDeterminant)
{
    Matrix m = Matrix(2, 2, 0.0);

    m.add(0, 0, 1.0);
    m.add(0, 1, 5.0);
    m.add(1, 0, -3.0);
    m.add(1, 1, 2.0);

    double d = m.determinant();

    EXPECT_EQ(d, 17.0);
}

TEST(MatrixTest, Submatrix)
{
    Matrix m = Matrix(3, 3, 0.0);

    m.add(0, 0, 1.0);
    m.add(0, 1, 5.0);
    m.add(0, 2, 0.0);
    m.add(1, 0, -3.0);
    m.add(1, 1, 2.0);
    m.add(1, 2, 7.0);
    m.add(2, 0, 0.0);
    m.add(2, 1, 6.0);
    m.add(2, 2, -3.0);

    Matrix m1 = m.submatrix(0, 2);

    EXPECT_EQ(m1.at(0, 0), -3.0);
    EXPECT_EQ(m1.at(0, 1), 2.0);
    EXPECT_EQ(m1.at(1, 0), 0.0);
    EXPECT_EQ(m1.at(1, 1), 6.0);
}

TEST(MatrixTest, Submatrix4x4)
{
    Matrix A(4, 4, 0.0);
    A.add(0, 0, -6);
    A.add(0, 1, 1);
    A.add(0, 2, 1);
    A.add(0, 3, 6);
    A.add(1, 0, -8);
    A.add(1, 1, 5);
    A.add(1, 2, 8);
    A.add(1, 3, 6);
    A.add(2, 0, -1);
    A.add(2, 1, 0);
    A.add(2, 2, 8);
    A.add(2, 3, 2);
    A.add(3, 0, -7);
    A.add(3, 1, 1);
    A.add(3, 2, -1);
    A.add(3, 3, 1);

    Matrix submatrix = A.submatrix(2, 1);

    EXPECT_EQ(submatrix.at(0, 0), -6);
    EXPECT_EQ(submatrix.at(0, 1), 1);
    EXPECT_EQ(submatrix.at(0, 2), 6);
    EXPECT_EQ(submatrix.at(1, 0), -8);
    EXPECT_EQ(submatrix.at(1, 1), 8);
    EXPECT_EQ(submatrix.at(1, 2), 6);
    EXPECT_EQ(submatrix.at(2, 0), -7);
    EXPECT_EQ(submatrix.at(2, 1), -1);
    EXPECT_EQ(submatrix.at(2, 2), 1);
}

TEST(MatrixTest, MatrixMinor)
{
    Matrix mat(3, 3, 0.0);

    mat.add(0, 0, 3);
    mat.add(0, 1, 5);
    mat.add(0, 2, 0);
    mat.add(1, 0, 2);
    mat.add(1, 1, -1);
    mat.add(1, 2, -7);
    mat.add(2, 0, 6);
    mat.add(2, 1, -1);
    mat.add(2, 2, 5);

    double minor = mat.minor(1, 0);
    double minor1 = mat.minor(0, 0);
    EXPECT_EQ(minor, 25);
    EXPECT_EQ(minor1, -12);
}

TEST(MatrixTest, Cofactor)
{
    Matrix mat(3, 3, 0.0);

    mat.add(0, 0, 3);
    mat.add(0, 1, 5);
    mat.add(0, 2, 0);
    mat.add(1, 0, 2);
    mat.add(1, 1, -1);
    mat.add(1, 2, -7);
    mat.add(2, 0, 6);
    mat.add(2, 1, -1);
    mat.add(2, 2, 5);

    double minor = mat.minor(1, 0);
    double minor1 = mat.minor(0, 0);
    double cofactor = mat.cofactor(1, 0);
    double cofactor1 = mat.cofactor(0, 0);

    EXPECT_EQ(minor, 25);
    EXPECT_EQ(cofactor, -25);
    EXPECT_EQ(minor1, -12);
    EXPECT_EQ(cofactor1, -12);
}

TEST(MatrixTest, Determinant3x3)
{
    Matrix A(3, 3, 0.0);
    A.add(0, 0, 1);
    A.add(0, 1, 2);
    A.add(0, 2, 6);
    A.add(1, 0, -5);
    A.add(1, 1, 8);
    A.add(1, 2, -4);
    A.add(2, 0, 2);
    A.add(2, 1, 6);
    A.add(2, 2, 4);

    double determinant = A.determinant();

    EXPECT_EQ(determinant, -196);
}

TEST(MatrixTest, Determinant4x4)
{
    Matrix A(4, 4, 0.0);
    A.add(0, 0, -2);
    A.add(0, 1, -8);
    A.add(0, 2, 3);
    A.add(0, 3, 5);
    A.add(1, 0, -3);
    A.add(1, 1, 1);
    A.add(1, 2, 7);
    A.add(1, 3, 3);
    A.add(2, 0, 1);
    A.add(2, 1, 2);
    A.add(2, 2, -9);
    A.add(2, 3, 6);
    A.add(3, 0, -6);
    A.add(3, 1, 7);
    A.add(3, 2, 7);
    A.add(3, 3, -9);

    double determinant = A.determinant();

    EXPECT_EQ(determinant, -4071);
}

TEST(MatrixTests, CalculateInverse)
{
    Matrix A = Matrix();

    A.add(0, 0, -5);
    A.add(0, 1, 2);
    A.add(0, 2, 6);
    A.add(0, 3, -8);
    A.add(1, 0, 1);
    A.add(1, 1, -5);
    A.add(1, 2, 1);
    A.add(1, 3, 8);
    A.add(2, 0, 7);
    A.add(2, 1, 7);
    A.add(2, 2, -6);
    A.add(2, 3, -7);
    A.add(3, 0, 1);
    A.add(3, 1, -3);
    A.add(3, 2, 7);
    A.add(3, 3, 4);

    Matrix B = A.inverse();
    EXPECT_DOUBLE_EQ(A.determinant(), 532);
    EXPECT_DOUBLE_EQ(A.cofactor(2, 3), -160);
    EXPECT_DOUBLE_EQ(B.at(3, 2), -160.0 / 532);
    EXPECT_DOUBLE_EQ(A.cofactor(3, 2), 105);
    EXPECT_DOUBLE_EQ(B.at(2, 3), 105.0 / 532);

    EXPECT_NEAR(B.at(0, 0), 0.21805, 1e-5);
    EXPECT_NEAR(B.at(0, 1), 0.45113, 1e-5);
    EXPECT_NEAR(B.at(0, 2), 0.24060, 1e-5);
    EXPECT_NEAR(B.at(0, 3), -0.04511, 1e-5);
    EXPECT_NEAR(B.at(1, 0), -0.80827, 1e-5);
    EXPECT_NEAR(B.at(1, 1), -1.45677, 1e-5);
    EXPECT_NEAR(B.at(1, 2), -0.44361, 1e-5);
    EXPECT_NEAR(B.at(1, 3), 0.52068, 1e-5);
    EXPECT_NEAR(B.at(2, 0), -0.07895, 1e-5);
    EXPECT_NEAR(B.at(2, 1), -0.22368, 1e-5);
    EXPECT_NEAR(B.at(2, 2), -0.05263, 1e-5);
    EXPECT_NEAR(B.at(2, 3), 0.19737, 1e-5);
    EXPECT_NEAR(B.at(3, 0), -0.52256, 1e-5);
    EXPECT_NEAR(B.at(3, 1), -0.81391, 1e-5);
    EXPECT_NEAR(B.at(3, 2), -0.30075, 1e-5);
    EXPECT_NEAR(B.at(3, 3), 0.30639, 1e-5);
}

TEST(MatrixTests, InverseOfAnotherMatrix)
{
    Matrix A(4, 4, 0.0);
    A.add(0, 0, 8);
    A.add(0, 1, -5);
    A.add(0, 2, 9);
    A.add(0, 3, 2);
    A.add(1, 0, 7);
    A.add(1, 1, 5);
    A.add(1, 2, 6);
    A.add(1, 3, 1);
    A.add(2, 0, -6);
    A.add(2, 1, 0);
    A.add(2, 2, 9);
    A.add(2, 3, 6);
    A.add(3, 0, -3);
    A.add(3, 1, 0);
    A.add(3, 2, -9);
    A.add(3, 3, -4);

    Matrix expected(4, 4, 0.0);
    expected.add(0, 0, -0.15385);
    expected.add(0, 1, -0.15385);
    expected.add(0, 2, -0.28205);
    expected.add(0, 3, -0.53846);
    expected.add(1, 0, -0.07692);
    expected.add(1, 1, 0.12308);
    expected.add(1, 2, 0.02564);
    expected.add(1, 3, 0.03077);
    expected.add(2, 0, 0.35897);
    expected.add(2, 1, 0.35897);
    expected.add(2, 2, 0.43590);
    expected.add(2, 3, 0.92308);
    expected.add(3, 0, -0.69231);
    expected.add(3, 1, -0.69231);
    expected.add(3, 2, -0.76923);
    expected.add(3, 3, -1.92308);

    Matrix result = A.inverse();

    for (int row = 0; row < expected.rowSize(); ++row)
    {
        for (int col = 0; col < expected.colSize(); ++col)
        {
            EXPECT_NEAR(result.at(row, col), expected.at(row, col), 1e-5);
        }
    }
}

TEST(MatrixTests, InverseOfThirdMatrix)
{
    Matrix A(4, 4, 0.0);
    A.add(0, 0, 9);
    A.add(0, 1, 3);
    A.add(0, 2, 0);
    A.add(0, 3, 9);
    A.add(1, 0, -5);
    A.add(1, 1, -2);
    A.add(1, 2, -6);
    A.add(1, 3, -3);
    A.add(2, 0, -4);
    A.add(2, 1, 9);
    A.add(2, 2, 6);
    A.add(2, 3, 4);
    A.add(3, 0, -7);
    A.add(3, 1, 6);
    A.add(3, 2, 6);
    A.add(3, 3, 2);

    Matrix expected(4, 4, 0.0);
    expected.add(0, 0, -0.04074);
    expected.add(0, 1, -0.07778);
    expected.add(0, 2, 0.14444);
    expected.add(0, 3, -0.22222);
    expected.add(1, 0, -0.07778);
    expected.add(1, 1, 0.03333);
    expected.add(1, 2, 0.36667);
    expected.add(1, 3, -0.33333);
    expected.add(2, 0, -0.02901);
    expected.add(2, 1, -0.14630);
    expected.add(2, 2, -0.10926);
    expected.add(2, 3, 0.12963);
    expected.add(3, 0, 0.17778);
    expected.add(3, 1, 0.06667);
    expected.add(3, 2, -0.26667);
    expected.add(3, 3, 0.33333);

    Matrix result = A.inverse();

    for (int row = 0; row < expected.rowSize(); ++row)
    {
        for (int col = 0; col < expected.colSize(); ++col)
        {
            EXPECT_NEAR(result.at(row, col), expected.at(row, col), 1e-5);
        }
    }
}

TEST(MatrixTests, MultiplyingProductByInverse)
{
    Matrix A(4, 4, 0.0);
    A.add(0, 0, 3);
    A.add(0, 1, -9);
    A.add(0, 2, 7);
    A.add(0, 3, 3);
    A.add(1, 0, 3);
    A.add(1, 1, -8);
    A.add(1, 2, 2);
    A.add(1, 3, -9);
    A.add(2, 0, -4);
    A.add(2, 1, 4);
    A.add(2, 2, 4);
    A.add(2, 3, 1);
    A.add(3, 0, -6);
    A.add(3, 1, 5);
    A.add(3, 2, -1);
    A.add(3, 3, 1);

    Matrix B(4, 4, 0.0);
    B.add(0, 0, 8);
    B.add(0, 1, 2);
    B.add(0, 2, 2);
    B.add(0, 3, 2);
    B.add(1, 0, 3);
    B.add(1, 1, -1);
    B.add(1, 2, 7);
    B.add(1, 3, 0);
    B.add(2, 0, 7);
    B.add(2, 1, 0);
    B.add(2, 2, 5);
    B.add(2, 3, 4);
    B.add(3, 0, 6);
    B.add(3, 1, -2);
    B.add(3, 2, 0);
    B.add(3, 3, 5);

    Matrix C = A * B;

    Matrix result = C * B.inverse();

    for (int row = 0; row < A.rowSize(); ++row)
    {
        for (int col = 0; col < A.colSize(); ++col)
        {
            EXPECT_NEAR(result.at(row, col), A.at(row, col), 1e-5);
        }
    }
}
