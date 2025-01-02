#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>
#include "Tuple.h"

using std::vector;

class Matrix
{
private:
    int m_rowSize;
    int m_colSize;
    vector<vector<double>> m_matrix;

public:
    Matrix();
    Matrix(int rowSize, int colSize, double initial);
    Matrix(std::initializer_list<std::initializer_list<double>> init);

    static const Matrix ID_MAT;

    void add(int row, int col, double value);
    double at(int row, int col) const;
    const double determinant() const;
    const Matrix inverse() const;
    const Matrix transpose()const ;
    const double minor(int row, int col) const;
    const double cofactor(int row, int col) const;
    const Matrix submatrix(int row, int col) const;

    int rowSize();
    int colSize();

    bool operator==(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Tuple operator*(const Tuple &tup) const;
    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);
};

#endif