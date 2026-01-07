#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

class SpanSet;

class Vector : private std::vector<double>
{
public:
    Vector();

    Vector(int size);

    Vector(std::vector<double> source);

    Vector(Vector const& source);

    void setSize(int size);

    double &operator[](int index);

    double operator[](int index) const;

    Vector &operator=(const Vector &other);

    Vector operator+(const Vector &other) const;

    Vector operator-(const Vector &other) const;

    double operator*(const Vector &other) const;

    Vector operator*(double num) const;

    Vector operator/(double num) const;

    Vector &operator*=(double num);

    Vector &operator/=(double num);

    Vector &operator+=(const Vector &other);

    Vector &operator-=(const Vector &other);

    Vector append(const Vector &other) const;

    Vector append(double num) const;

    Vector cross(const Vector &other) const;

    double norm() const;

    Vector unit() const;

    bool isFullZero() const;

    bool isFullZeroAfter(int &index) const;

    static Vector proj(const Vector &base, const Vector &target);

    static Vector perp(const Vector &base, const Vector &target);

    int dim() const;

    friend class SpanSet;
};

#endif // VECTOR_H
