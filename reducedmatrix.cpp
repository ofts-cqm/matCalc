#include "reducedmatrix.h"
#include "dimensionmismatchexception.h"
#include "util.h"
#include <cassert>

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

bool ReducedMatrix::hasSolu() const {
    return rank(false) == rank(true);
}

Matrix ReducedMatrix::getSolutionMatrix(bool withVector) const {
    int width = (boundary == -1 || !withVector ? getWidth() : boundary), height = getHeight();

    // varColumn: index is ith var, value is matrix column
    // varRow: same, but value is the row that needs the var
    std::vector<int> varColumn, varRow;
    int pivotRow = 0;
    for (int i = 0; i < width; i++){
        if (isZero(column(i)[pivotRow])) {
            varColumn.push_back(i);
            varRow.push_back(pivotRow + varRow.size());
        } else pivotRow++;
    }

    for(int i = width; i < height; i++){
        varColumn.push_back(-1);
        varRow.push_back(i);
    }

    const int matOffSet = withVector;
    Vector equVec = augmentedVector();
    Matrix sol = Matrix(height, varColumn.size() + matOffSet);
    for (int i = 0; i < height; i++){
        if (withVector) sol[i, 0] = equVec[i];

        for (int j = 0; j < varColumn.size(); j++){
            if (varRow[j] == i) sol[i, j + matOffSet] = 1;
            else if (varColumn[j] != -1) sol[i, j + matOffSet] = -(* this)[i, varColumn[j]];
        }
    }

    return sol;
}

std::vector<bool> ReducedMatrix::pivots(){
    int row = 0;
    std::vector<bool> pivots;
    for (int i = 0; i < getWidth(); i++){
        if (isZero((*this)[row, i])){
            pivots.push_back(false);
        }else{
            pivots.push_back(true);
            row++;
        }
    }
    return pivots;
}

int ReducedMatrix::rank(bool augmented) const{
    Matrix mat = augmented ? (Matrix)(* this) : this->mainMatrix();
    int start = 0;
    for (int i = 0; i < this->getHeight(); i++){
        if (mat[i].isFullZeroAfter(start)) return i;
    }
    return this->getHeight();
}

Matrix ReducedMatrix::mainMatrix() const{
    int boundary = this->boundary == -1 ? this->getWidth() : this->boundary;
    Matrix mat(this->getHeight(), boundary);
    for (int i = 0; i < this->getHeight(); i++){
        Vector vec = (*this)[i];
        vec.setSize(boundary);
        mat[i] = vec;
    }
    return mat;
}

Matrix ReducedMatrix::augmentedMatrix() const{
    assert(this->boundary != -1);
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
    if (this->boundary == -1) return Vector(this->getHeight());

    Vector vec(this->getHeight());
    for (int i = 0; i < this->getHeight(); i++){
        vec[i] = (* this)[i, this->boundary];
    }
    return vec;
}
