#include "vector.h"
#include "../dimensionmismatchexception.h"
#include "../util.h"
#include <cmath>

Vector::Vector(): std::vector<double>() {}

//Vector::Vector(std::vector<double> source): std::vector<double>(source) {}

Vector::Vector(std::vector<double> source) : Vector(source.size()){
    std::vector<double>::operator=(source);
}

Vector::Vector(int size): std::vector<double>() {
    this->resize(size, 0);
}

Vector::Vector(Vector const& source): Vector((std::vector<double>)source){

}

void Vector::setSize(int size){
    this->resize(size, 0);
}

double &Vector::operator[](int index){
    if (index >= dim()) throwRangeException(index, dim());
    return std::vector<double>::operator[](index);
}

double Vector::operator[](int index) const{
    if (index >= dim()) throwRangeException(index, dim());
    return std::vector<double>::operator[](index);
}

Vector &Vector::operator=(const Vector &other){
    std::vector<double>::operator=(other);
    return *this;
}

Vector Vector::operator+(const Vector &other) const{
    if (this->dim() != other.dim())
        throw new DimensionMismatchException(this->dim(), other.dim());

    Vector newVec(other.dim());

    for (int i = 0; i < this->dim(); i++){
        newVec[i] = (* this)[i] + other[i];
    }

    return newVec;
}

Vector Vector::operator-(const Vector &other) const{
    if (this->dim() != other.dim())
        throw new DimensionMismatchException(this->dim(), other.dim());

    Vector newVec(other.dim());

    for (int i = 0; i < this->dim(); i++){
        newVec[i] = (* this)[i] - other[i];
    }

    return newVec;
}


double Vector::operator*(const Vector &other) const{
    if (this->dim() != other.dim())
        throw new DimensionMismatchException(this->dim(), other.dim());

    double res = 0;

    for (int i = 0; i < this->dim(); i++){
        res += (* this)[i] * other[i];
    }

    return res;
}

Vector Vector::operator*(double num) const{
    Vector newVec(*this);

    for (int i = 0; i < this->dim(); i++){
        newVec[i] *= num;
    }

    return newVec;
}

Vector Vector::operator/(double num) const{
    Vector newVec(*this);
    return newVec /= num;
}

Vector &Vector::operator*=(double num){
    for (int i = 0; i < this->dim(); i++){
        (* this)[i] *= num;
    }

    return *this;
}

Vector &Vector::operator/=(double num){
    for (int i = 0; i < this->dim(); i++){
        (* this)[i] /= num;
    }

    return *this;
}

Vector &Vector::operator+=(const Vector &other){
    if (this->dim() != other.dim())
        throw new DimensionMismatchException(this->dim(), other.dim());

    for (int i = 0; i < this->dim(); i++){
        (* this)[i] += other[i];
    }

    return *this;
}

Vector &Vector::operator-=(const Vector &other){
    if (this->dim() != other.dim())
        throw new DimensionMismatchException(this->dim(), other.dim());

    for (int i = 0; i < this->dim(); i++){
        (* this)[i] -= other[i];
    }

    return *this;
}

Vector Vector::append(const Vector &other) const{
    Vector newVec(*this);
    newVec.append_range((std::vector<double>)other);
    return newVec;
}

Vector Vector::append(double num) const{
    Vector newVec(*this);
    newVec.append(num);
    return newVec;
}

Vector Vector::cross(const Vector &other) const{
    if (this->dim() != 3)
        throw new DimensionMismatchException(this->dim(), 3);
    if (other.dim() != 3)
        throw new DimensionMismatchException(other.dim(), 3);

    double a = (* this)[1] * other[2] - (* this)[2] * other[1];
    double b = (* this)[2] * other[0] - (* this)[0] * other[2];
    double c = (* this)[0] * other[1] - (* this)[1] * other[0];

    return Vector({a, b, c});
}

Vector Vector::proj(const Vector &base, const Vector &target){
    return base * ((target * base) / (base * base));
}

Vector Vector::perp(const Vector &base, const Vector &target){
    return target - proj(base, target);
}

double Vector::norm() const{
    double res = 0;

    for (int i = 0; i < this->dim(); i++){
        res += this[i] * this[i];
    }

    return std::sqrt(res);
}

Vector Vector::unit() const{
    return *this * (1 / this->norm());
}

bool Vector::isFullZero() const{
    int start = 0;
    return isFullZeroAfter(start);
}

bool Vector::isFullZeroAfter(int &index) const{
    int initial = index;
    for (; index < this->dim(); index++){
        if (!isZero((* this)[index])) return false & index++;
    }
    index = initial;
    return true;
}

int Vector::dim() const{
    return this->size();
}
