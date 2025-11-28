#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

class Vector : private std::vector<double>
{
public:
    Vector();

    Vector(int size);

    Vector(std::vector<double> source);

    void setSize(int size);

    double &operator[](int index);

    double operator[](int index) const;

    Vector &operator=(const Vector &other);

    Vector operator+(const Vector &other) const;

    Vector operator-(const Vector &other) const;

    double operator*(const Vector &other) const;

    Vector operator*(double num) const;

    Vector cross(const Vector &other) const;

    double norm() const;

    Vector unit() const;

    int dim() const;
};

#endif // VECTOR_H
