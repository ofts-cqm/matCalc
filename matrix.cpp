#include "matrix.h"
#include "dimensionmismatchexception.h"
#include "reducedmatrix.h"
#include "spanset.h"
#include "util.h"
#include <cmath>


Matrix::Matrix(): Matrix(0, 0){}

Matrix::Matrix(int height, int width){
    entries.resize(height, Vector(width));
    this->width = width;
    this->height = height;
}

Matrix::Matrix(const Matrix &other){
    this->entries = other.entries;
    this->height = other.height;
    this->width = other.width;
}

Matrix Matrix::unit(int size){
    Matrix mat(size, size);

    for (int i = 0; i < size; i++){
        mat[i, i] = 1;
    }

    return mat;
}

int Matrix::getHeight() const { return this->height; }

int Matrix::getWidth() const { return this->width; }

void Matrix::resize(int height, int width){
    if (width == -1) width = this->width;
    if (height == -1) height = this->height;

    this->width = width;
    this->height = height;

    entries.resize(height);

    for (Vector &vector : entries){
        vector.setSize(width);
    }
}

Matrix &Matrix::operator=(const Matrix &other){
    this->entries = other.entries;
    this->height = other.height;
    this->width = other.width;

    return *this;
}

double &Matrix::operator[](int i, int j){
    return entries[i][j];
}

const double Matrix::operator[](int i, int j) const{
    return entries[i][j];
}

const Vector &Matrix::operator[](int i) const{
    return entries[i];
}

Vector &Matrix::operator[](int i){
    return entries[i];
}


const Vector Matrix::column(int i) const{
    Vector vec(this->height);

    for (int j = 0; j < height; j++){
        vec[j] = entries[j][i];
    }

    return vec;
}

Matrix Matrix::operator+(const Matrix &other) const{
    if (this->height != other.height) throw new DimensionMismatchException(this->height, other.height, "height");
    if (this->width != other.width) throw new DimensionMismatchException(this->width, other.width, "width");

    Matrix matrix(this->height, this->width);

    for (int i = 0; i < height; i++){
        matrix[i] = entries[i] + other[i];
    }

    return matrix;
}

Matrix Matrix::operator-(const Matrix &other) const{
    if (this->height != other.height) throw new DimensionMismatchException(this->height, other.height, "height");
    if (this->width != other.width) throw new DimensionMismatchException(this->width, other.width, "width");

    Matrix matrix(this->height, this->width);

    for (int i = 0; i < height; i++){
        matrix[i] = entries[i] - other[i];
    }

    return matrix;
}

Matrix Matrix::operator*(const double scale) const{
    Matrix res = *this;

    for (int i = 0; i < height; i++){
        res[i] *= scale;
    }

    return res;
}

Vector Matrix::operator*(const Vector &vector) const{
    if (this->width != vector.dim()) throw new DimensionMismatchException(this->width, vector.dim());

    Vector res(this->height);

    for (int i = 0; i < height; i++){
        res[i] = entries[i] * vector;
    }

    return res;
}

Matrix Matrix::operator*(const Matrix &other) const{
    if (this->width != other.height) throw new DimensionMismatchException(this->width, other.height, "Intermediate Dimension");

    Matrix trans = other.transpose(), res(this->height, other.width);

    for (int i = 0; i < height; i++){
        for (int j = 0; j < other.width; j++){
            res[i, j] = entries[i] * trans[j];
        }
    }

    return res;
}

Matrix Matrix::transpose() const{
    Matrix res(this->width, this->height);

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            res[j, i] = entries[i][j];
        }
    }

    return res;
}

SpanSet Matrix::nullSpace() const {
    return SpanSet(reduce().getSolutionMatrix());
}

SpanSet Matrix::colSpace() const{
    return SpanSet(*this).reduce();
}

void Matrix::rowSwap(const int a, const int b){
    Vector temp = entries[a];
    entries[a] = entries[b];
    entries[b] = temp;
}

double Matrix::det() const{
    if (this->height != this->width) throw new DimensionMismatchException(this->height, this->width);

    if (this->height == 0) return 0;
    if (this->height == 1) return entries[0][0];
    if (this->height == 2) return entries[0][0] * entries[1][1] - entries[0][1] * entries[1][0];

    double det = 1.0;
    int sign = 1, n = this->height;
    Matrix m = *this;

    for (int i = 0; i < n; i++) {
        // Pivot selection
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(m[j, i]) > fabs(m[pivot, i])) {
                pivot = j;
            }
        }

        // If pivot is zero, determinant is zero
        if (fabs(m[pivot, i]) < 1e-9) {
            return 0.0;
        }

        // Swap rows if needed
        if (pivot != i) {
            m.rowSwap(pivot, i);
            sign = -sign;
        }

        // Eliminate below
        for (int j = i + 1; j < n; j++) {
            double factor = m[j, i] / m[i, i];
            m[j] -= m[i] * factor;
        }

        det *= m[i, i];
    }

    return det * sign;
}

int Matrix::firstNonZeroInColumn(int column, int fromIndex) const{
    for (int i = fromIndex; i < height; i++) {
        if (!isZero(entries[i][column])) return i;
    }
    return -1;
}

void clearEntry(Matrix &matrix, int row, int pivot, int startingIndex){
    if (isZero(matrix[row, startingIndex])) return;
    double multiplier = matrix[row, startingIndex];
    matrix[row] -= matrix[pivot] * multiplier;
}

void Matrix::ref(int fromIndex, int& startingColumn){
    // find the pivot entry
    int nonZeroIndex = firstNonZeroInColumn(startingColumn, fromIndex);
    while (nonZeroIndex == -1){
        // no pivot entry??? next row!
        startingColumn++;
        if (startingColumn == width) return;
        nonZeroIndex = firstNonZeroInColumn(startingColumn, fromIndex);
    }

    // if the current row (from index) is not the row containing pivot entry...
    // just swap them
    if (fromIndex != nonZeroIndex){
        rowSwap(fromIndex, nonZeroIndex);
        nonZeroIndex = fromIndex;
    }

    // reduce the pivot entry to one.
    // this is not necessary in ref, but for convenience in later calculation, we reduce to 1
    entries[nonZeroIndex] /= entries[nonZeroIndex][startingColumn];
    for (int i = nonZeroIndex + 1; i < height; i++) {
        clearEntry(*this, i, nonZeroIndex, startingColumn);
    }
    // next time, start in the next column
    startingColumn ++;
}

ReducedMatrix Matrix::reduce() const {
    return reduceAsMatrix();
}

Matrix Matrix::reduceAsMatrix() const{
    int startingColumn = 0, refed_row = 0;
    Matrix mat = *this;

    // reduce each column to ref form
    while (startingColumn != width && refed_row != height) mat.ref(refed_row++, startingColumn);

    // in ref, we already cleared rows below each pivot entry.
    // now, we need to clear rows above each pivot entry
    int currentRow = 0;
    for (int i = 0; i < width; i++) { // scan from left to right
        if (currentRow == height) break; // break if reached bottom
        if (isZero(mat[currentRow, i])) continue; // skip if not pivot entry

        // we found a pivot entry! clear all rows from row 0 to this row!
        for (int j = 0; j < currentRow; j++) {
            clearEntry(mat, j, currentRow, i);
        }
        currentRow++;
    }

    // done!
    return mat;
}
