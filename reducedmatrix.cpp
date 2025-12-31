#include "reducedmatrix.h"
#include "dimensionmismatchexception.h"

ReducedMatrix::ReducedMatrix(): Matrix() {
    this->boundary = -1;
}

ReducedMatrix::ReducedMatrix(const ReducedMatrix &other)
    : ReducedMatrix((Matrix)other, other.boundary){}

ReducedMatrix::ReducedMatrix(const Matrix &other)
    : ReducedMatrix(other, -1){}

ReducedMatrix::ReducedMatrix(const Matrix &other, int boundary)
    : Matrix(other){
    this->boundary = boundary;
}

ReducedMatrix ReducedMatrix::reduce(const Matrix &matrix){
    return matrix.reduce();
}

ReducedMatrix ReducedMatrix::reduce(const Matrix &matrix, const Matrix &augmentedMatrix){
    if (matrix.getHeight() != augmentedMatrix.getHeight()) throw new DimensionMismatchException(matrix.getHeight(), augmentedMatrix.getHeight(), "height");
    Matrix combined = Matrix(matrix.getHeight(), matrix.getWidth() + augmentedMatrix.getWidth());
    for (int i = 0; i < matrix.getHeight(); i++){
        combined[i] = matrix[i].append(augmentedMatrix[i]);
    }
    return ReducedMatrix(combined.reduceAsMatrix(), matrix.getWidth());
}

ReducedMatrix ReducedMatrix::reduce(const Matrix &matrix, const Vector &vector){
    if (matrix.getHeight() != vector.dim()) throw new DimensionMismatchException(matrix.getHeight(), vector.dim(), "height");
    Matrix combined = Matrix(matrix.getHeight(), matrix.getWidth() + 1);
    for (int i = 0; i < matrix.getHeight(); i++){
        combined[i] = matrix[i].append(vector[i]);
    }
    return ReducedMatrix(combined.reduceAsMatrix(), matrix.getWidth());
}

void ReducedMatrix::resize(int height, int width){
    Matrix::resize(height, width);
    if (this->boundary > this->getWidth()) throw new DimensionMismatchException(this->boundary, this->getWidth(), "width");
}

ReducedMatrix &ReducedMatrix::operator=(const ReducedMatrix &other) {
    Matrix::operator=(other);
    this->boundary = other.boundary;
    return *this;
}

int ReducedMatrix::rank() const{
    for (int i = 0; i < this->getHeight(); i++){
        if ((* this)[i].isFullZero()) return i;
    }
    return this->getHeight();
}

Matrix ReducedMatrix::mainMatrix() const{
    Matrix mat(this->getHeight(), this->boundary);
    for (int i = 0; i < this->getHeight(); i++){
        Vector vec = (*this)[i];
        vec.setSize(this->boundary);
        mat[i] = vec;
    }
    return mat;
}

Matrix ReducedMatrix::augmentedMatrix() const{
    int w = this->getWidth() - this->boundary;
    Matrix mat(this->getHeight(), w);
    for (int i = 0; i < this->getHeight(); i++){
        Vector vec(w);
        for (int j = 0; j < w; j++){
            vec[j] = (*this)[i, j + boundary];
        }
        mat[i] = vec;
    }
    return mat;
}

Vector ReducedMatrix::augmentedVector() const{
    Vector vec(this->getHeight());
    for (int i = 0; i < this->getHeight(); i++){
        vec[i] = (* this)[i, this->boundary];
    }
    return vec;
}
