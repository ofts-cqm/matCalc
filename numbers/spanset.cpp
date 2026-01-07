#include "spanset.h"
#include "reducedmatrix.h"
#include "../dimensionmismatchexception.h"

SpanSet::SpanSet(): Matrix() {}

SpanSet::SpanSet(int vecDim, int spaceDim): Matrix(vecDim, spaceDim) {}

SpanSet::SpanSet(const SpanSet &other): Matrix(other) {}

SpanSet::SpanSet(const Matrix &base): Matrix(base) {}

Matrix &SpanSet::asMatrix() { return *this; }

const Matrix &SpanSet::asMatrix() const { return *this; }

double &SpanSet::operator[](int i, int j){ return Matrix::operator[](i, j); }

const double SpanSet::operator[](int i, int j) const { return Matrix::operator[](i, j); }

const Vector SpanSet::operator[](int i) const { return Matrix::column(i); }

SpanSet SpanSet::operator+(const Vector &vec) const{
    if (this->height != vec.dim()) throw new DimensionMismatchException(this->height, vec.dim(), "Vector Dimension");

    SpanSet set = *this;
    set.width++;
    for (int i = 0; i < this->height; i++){
        set.Matrix::operator[](i).push_back(vec[i]);
    }

    return set;
}

SpanSet SpanSet::operator+(const SpanSet &other) const{
    if (this->height != other.height) throw new DimensionMismatchException(this->height, other.height, "Vector Dimension");

    SpanSet set = *this;
    set.width += other.width;
    for (int i = 0; i < this->height; i++){
        set.Matrix::operator[](i).append(other.Matrix::operator[](i));
    }
    return set;
}

SpanSet &SpanSet::operator+=(const Vector &vec){
    if (this->height != vec.dim()) throw new DimensionMismatchException(this->height, vec.dim(), "Vector Dimension");

    this->width++;
    for (int i = 0; i < this->height; i++){
        Matrix::operator[](i).push_back(vec[i]);
    }

    return *this;
}

SpanSet &SpanSet::operator+=(const SpanSet &other){
    if (this->height != other.height) throw new DimensionMismatchException(this->height, other.height, "Vector Dimension");

    this->width += other.width;
    for (int i = 0; i < this->height; i++){
        Matrix::operator[](i).append(other.Matrix::operator[](i));
    }
    return *this;
}

SpanSet SpanSet::operator&(const std::vector<bool> cols) const{
    if (this->width != cols.size()) throw new DimensionMismatchException(this->width, cols.size(), "Vector Length");

    SpanSet set(this->height, 0);
    for (int i = 0; i < cols.size(); i++){
        if (cols[i]) set += (* this)[i];
    }
    return set;
}

SpanSet &SpanSet::operator&=(const std::vector<bool> cols){
    if (this->width != cols.size()) throw new DimensionMismatchException(this->width, cols.size(), "Vector Length");

    SpanSet set = *this;
    this->entries.clear();
    this->width = 0;
    for (int i = 0; i < cols.size(); i++){
        if (cols[i]) *this += set[i];
    }
    return *this;
}

SpanSet SpanSet::reduce() const{
    return *this & Matrix::reduce().pivots();
}

SpanSet SpanSet::extend() const{
    return (*this + SpanSet(Matrix::unit(this->getHeight()))).reduce();
}

int SpanSet::spans() const{
    return Matrix::reduce().rank();
}

bool SpanSet::includes(const Vector &vec) const{
    return ReducedMatrix::reduce(*this, vec).hasSolu();
}
