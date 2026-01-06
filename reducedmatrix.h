#ifndef REDUCEDMATRIX_H
#define REDUCEDMATRIX_H

#include "matrix.h"

class ReducedMatrix : public Matrix
{
public:
    ReducedMatrix();

    ReducedMatrix(const ReducedMatrix &other);

    static ReducedMatrix reduce(const Matrix &matrix);
    static ReducedMatrix reduce(const Matrix &matrix, const Matrix &augmented);
    static ReducedMatrix reduce(const Matrix &matrix, const Vector &vector);

    virtual void resize(int height = -1, int width = -1) override;

    ReducedMatrix &operator=(const ReducedMatrix &other);

    int rank(bool augmented = false) const;

    bool hasSolu() const;

    Matrix getSolutionMatrix(bool withVector) const;

    std::vector<bool> pivots();

    Matrix mainMatrix() const;

    Matrix augmentedMatrix() const;

    Vector augmentedVector() const;

private:
    friend class Matrix;

    ReducedMatrix(const Matrix &other);

    ReducedMatrix(const Matrix &other, int boundary);

    int boundary;
};

#endif // REDUCEDMATRIX_H
