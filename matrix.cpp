#include "matrix.h"
#include "dimensionmismatchexception.h"


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

    for (int j = 0; i < height; j++){
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

double Matrix::det() const{
    if (this->height != this->width) throw new DimensionMismatchException(this->height, this->width);

    if (this->height == 0) return 0;
    if (this->height == 1) return entries[0][0];
    if (this->height == 2) return entries[0][0] * entries[1][1] - entries[0][1] * entries[1][0];

    // TODO: Implement This
}

Matrix Matrix::reduce() const{
    // TODO: Implement This
}
