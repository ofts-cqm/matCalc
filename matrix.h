#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

class ReducedMatrix;

class Matrix
{
public:
    Matrix();

    Matrix(int height, int width);

    Matrix(const Matrix &other);

    static Matrix unit(int size);

    int getHeight() const;

    int getWidth() const;

    virtual void resize(int height = -1, int width = -1);

    Matrix &operator=(const Matrix &other);

    double &operator[](int i, int j);

    const double operator[](int i, int j) const;

    Vector &operator [](int i);

    const Vector &operator [](int i) const;

    const Vector column(int i) const;

    Matrix operator+(const Matrix &other) const;

    Matrix operator-(const Matrix &other) const;

    Matrix operator*(const double scale) const;

    Vector operator*(const Vector &vector) const;

    Matrix operator*(const Matrix &other) const;

    Matrix transpose() const;

    double det() const;

    ReducedMatrix reduce() const;

    Matrix reduceAsMatrix() const;

private:
    friend class SpanSet;

    void ref(int fromIndex, int& startingColumn);

    int firstNonZeroInColumn(const int column, const int fromIndex) const;

    void rowSwap(const int a, const int b);

    int width, height;
    std::vector<Vector> entries;
};

#endif // MATRIX_H
