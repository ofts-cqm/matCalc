#ifndef SPANSET_H
#define SPANSET_H

#include "matrix.h"

class SpanSet: private Matrix
{
public:
    SpanSet();

    SpanSet(int vecDim, int spaceDim);

    SpanSet(const SpanSet &other);

    explicit SpanSet(const Matrix &base);

    using Matrix::getHeight;
    using Matrix::getWidth;
    using Matrix::resize;
    using Matrix::operator=;

    Matrix &asMatrix();

    double &operator[](int i, int j);

    const double operator[](int i, int j) const;

    const Vector operator [](int i) const;

    SpanSet operator+(const Vector &vec) const;

    SpanSet operator+(const SpanSet &other) const;

    SpanSet &operator+=(const Vector &vec);

    SpanSet &operator+=(const SpanSet &other);

    SpanSet operator&(const std::vector<bool> cols) const;

    SpanSet &operator&=(const std::vector<bool> cols);

    SpanSet reduce() const;

    SpanSet extend() const;

    int spans() const;

    bool includes(const Vector &vec) const;
};

#endif // SPANSET_H
