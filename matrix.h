#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

class Matrix
{
public:
    Matrix();

    Matrix(int height, int width);

    Matrix(const Matrix &other);

    int getHeight() const;

    int getWidth() const;

    void resize(int height = -1, int width = -1);

    Matrix &operator=(const Matrix &other);

    double &operator[](int i, int j);

    const double operator[](int i, int j) const;

    Vector &operator [](int i);

    const Vector &operator [](int i) const;

    const Vector column(int i) const;

    Matrix operator+(const Matrix &other) const;

    Matrix operator-(const Matrix &other) const;

    Vector operator*(const Vector &vector) const;

    Matrix operator*(const Matrix &other) const;

    Matrix transpose() const;

    double det() const;

    Matrix reduce() const;


private:
    int width, height;
    std::vector<Vector> entries;
};

#endif // MATRIX_H
