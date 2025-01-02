#include "Matrix.h"
#include <iomanip>
using namespace std;

Matrix::Matrix()
{
    m_rowSize = 4;
    m_colSize = 4;
    m_matrix.resize(4);
    for (unsigned i = 0; i < m_matrix.size(); i++)
    {
        m_matrix[i].resize(4, 0.0);
    }
}

Matrix::Matrix(int rowSize, int colSize, double initial)
{
    m_rowSize = rowSize;
    m_colSize = colSize;
    m_matrix.resize(rowSize);
    for (unsigned i = 0; i < m_matrix.size(); i++)
    {
        m_matrix[i].resize(colSize, initial);
    }
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> init)
{
    m_rowSize = init.size();
    m_colSize = init.begin()->size();
    m_matrix.resize(m_rowSize);

    int row = 0;
    for (const auto &rowList : init)
    {
        m_matrix[row].assign(rowList.begin(), rowList.end());
        ++row;
    }
}

const Matrix Matrix::ID_MAT = []()
{
    Matrix id(4, 4, 0.0);
    id.add(0, 0, 1.0);
    id.add(1, 1, 1.0);
    id.add(2, 2, 1.0);
    id.add(3, 3, 1.0);
    return id;
}();

void Matrix::add(int row, int col, double value)
{
    m_matrix[row][col] = value;
}

double Matrix::at(int row, int col) const
{
    return m_matrix[row][col];
}

const double Matrix::determinant() const
{
    double det = 0;
    if (m_rowSize == 2 && m_colSize == 2)
    {
        return m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];
    }

    for (int col = 0; col < m_colSize; col++)
    {
        det += m_matrix[0][col] * cofactor(0, col);
    }

    return det;
}

/// @brief Creates submatrix given row and col to remove
/// @param row
/// @param col
/// @return newMat - new submatrix
const Matrix Matrix::submatrix(int row, int col) const
{
    Matrix newMat = Matrix(m_rowSize - 1, m_colSize - 1, 0.0);

    int newRow = 0;
    for (int i = 0; i < m_rowSize; i++)
    {
        if (i == row)
        {
            continue;
        }
        int newCol = 0;
        for (int j = 0; j < m_colSize; j++)
        {
            if (j == col)
            {
                continue;
            }
            newMat.add(newRow, newCol, m_matrix[i][j]);
            newCol++;
        }
        newRow++;
    }

    return newMat;
}

/// @brief Calculates the minor for a given matrix
/// where minor is the determinant of a particular
/// submatrix
/// @param row
/// @param col
/// @return minor
const double Matrix::minor(int row, int col) const
{
    Matrix mat = submatrix(row, col);
    double minor = mat.determinant();

    return minor;
}

const double Matrix::cofactor(int row, int col) const
{
    int negative = (row + col) % 2 == 0 ? 1 : -1;
    double min = minor(row, col);

    return negative * min;
}

const Matrix Matrix::inverse() const
{
    double det = determinant();

    if (std::abs(det) < 1e-9)
    {
        throw std::invalid_argument("Matrix is not invertible");
    }

    Matrix m(m_rowSize, m_colSize, 0.0);

    for (int row = 0; row < m_rowSize; row++)
    {
        for (int col = 0; col < m_colSize; col++)
        {
            double c = cofactor(row, col);
            m.add(col, row, c / det);
        }
    }

    return m;
}

const Matrix Matrix::transpose() const
{
    Matrix m(m_rowSize, m_colSize, 0.0);

    for (int row = 0; row < m_rowSize; row++)
    {
        for (int col = 0; col < m_colSize; col++)
        {
            m.add(col, row, m_matrix[row][col]);
        }
    }

    return m;
}

int Matrix::rowSize()
{
    return m_rowSize;
}

int Matrix::colSize()
{
    return m_colSize;
}

bool Matrix::operator==(const Matrix &other) const
{
    if (m_rowSize != other.m_rowSize || m_colSize != other.m_colSize)
    {
        return false;
    }
    for (int i = 0; i < other.m_rowSize; i++)
    {
        for (int j = 0; j < other.m_colSize; j++)
        {
            if (m_matrix[i][j] != other.at(i, j))
            {
                return false;
            }
        }
    }

    return true;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    if (m_rowSize != 4 || m_colSize != 4 || other.m_rowSize != 4 || other.m_colSize != 4)
        throw std::invalid_argument("Only 4x4 matrices are supported in this raytracer");

    Matrix m = Matrix();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < 4; k++)
            {
                sum += m_matrix[i][k] * other.m_matrix[k][j];
            }
            m.add(i, j, sum);
        }
    }

    return m;
}

Tuple Matrix::operator*(const Tuple &tup) const
{
    if (m_rowSize != 4 || m_colSize != 4)
        throw std::invalid_argument("Matrix must be 4x4 to multiply with a Tuple");

    double x = m_matrix[0][0] * tup.x + m_matrix[0][1] * tup.y + m_matrix[0][2] * tup.z + m_matrix[0][3] * tup.w;
    double y = m_matrix[1][0] * tup.x + m_matrix[1][1] * tup.y + m_matrix[1][2] * tup.z + m_matrix[1][3] * tup.w;
    double z = m_matrix[2][0] * tup.x + m_matrix[2][1] * tup.y + m_matrix[2][2] * tup.z + m_matrix[2][3] * tup.w;
    double w = m_matrix[3][0] * tup.x + m_matrix[3][1] * tup.y + m_matrix[3][2] * tup.z + m_matrix[3][3] * tup.w;

    return Tuple(x, y, z, w);
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    os << "Matrix (" << mat.m_rowSize << "x" << mat.m_colSize << "):\n";

    for (int i = 0; i < mat.m_rowSize; ++i)
    {
        os << "[ ";
        for (int j = 0; j < mat.m_colSize; ++j)
        {
            os << std::fixed << std::setprecision(2) << std::setw(8) << mat.at(i, j) << " ";
        }
        os << "]\n";
    }
    return os;
}