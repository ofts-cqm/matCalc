#ifndef POLYNOMIALMATRIX_H
#define POLYNOMIALMATRIX_H

#include "matrix.h"
#include "polynomial.h"
class PolynomialMatrix: std::vector<std::vector<Polynomial>>
{
public:
    explicit PolynomialMatrix(const Matrix &matrix);

    using ::PolynomialMatrix::vector::operator=;
    using ::PolynomialMatrix::vector::operator[];

    const Polynomial &operator[](int i, int j) const;

    Polynomial recursiveDet(int size);

    Polynomial det() const;

    Matrix evaluate(double x) const;

    int size;

private:
    std::vector<bool> rows;
    std::vector<bool> cols;
};

#endif // POLYNOMIALMATRIX_H
