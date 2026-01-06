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

Matrix ReducedMatrix::getSolutionMatrix() const {
    int width = (boundary == -1 ? getWidth() : boundary), height = getHeight(), num_var = 0, last_exist = -1, variable[width];
    for (int i = 0; i < width; i++) variable[i] = 0;

    // for each variable, we want to know if it exists as a pivot point.
    // "variable" is used to store all function's variable's type.
    // "-1" simply means it's a pivot points
    // here, we search from up to down
    // to make sure we cover all variables, still use width as boundary
    for (int i = 0; i < width; i++) {
        // scan from left to right
        if (i < height) for (int j = last_exist + 1; j < width; j++) {
            // the first number we meet is the pivot entry
            if (!isZero(( *this)[i, j])) {
                variable[j] = -1; // record it as pivot entry
                last_exist = j; // all pivot entries are on the right side of this, so start from here
                goto lp; // search next row
            }
        }
        // if we cannot find a pivot entry, then this row and all below are full zero
        // we can record number of variables now.
        num_var = width - i;
        break;
        lp:
    }

    Matrix answerMatrix(num_var + 1, width);

    // here, we assign index to all free variables
    int assignedVariable = 0;
    for (int i = 0; i < width; i++) {
        if (variable[i] == 0) { // if a variable does not have pivot entry, it is free
            variable[i] = ++assignedVariable;// assign new index to this entry
            answerMatrix[i, assignedVariable] = 1;// set this variable's entry to 1
        }
    }

    // now, we iterate through the matrix to fill the answer matrix.
    // we search from up to down
    for (int i = 0; i < height; i++) {
        int pivot = -1;

        // first try to find a pivot entry
        for (int j = 0; j < width; j++) {
            if (!isZero((*this)[i, j])){
                pivot = j;
                break;
            }
        }

        // cannot find? congratulation! we reached the end!
        if (pivot == -1) break;

        // pivot entry are not important in this case because we are defining them
        // start from its right
        for (int j = pivot + 1; j < width; j++) {
            // if we find a non-zero entry
            if (!isZero((* this)[i, j])){
                // we use variable[j] to find this entry's related free-variable
                // and set this free-variable's value as the negative of the solved matrix's
                // negative because we implicitly moved the answer from right-hand-side
                // of the equal sign to the left-hand-side, so negative
                answerMatrix[pivot, variable[j]] = -(*this)[i, j];
            }
        }
        // don't forget to assign the trivial solution
        answerMatrix[pivot, 0] = -augmentedVector()[i];
    }

    return answerMatrix;
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
