#include "polynomialmatrix.h"
#include "../dimensionmismatchexception.h"

PolynomialMatrix::PolynomialMatrix(const Matrix &matrix): vector(), size(matrix.getHeight()) {
    if (matrix.getHeight() != matrix.getWidth())
        throw DimensionMismatchException(matrix.getHeight(), matrix.getWidth(), "size");

    this->resize(matrix.getHeight(), std::vector<Polynomial>(matrix.getWidth()));
    this->rows.resize(size, true);
    this->cols.resize(size, true);

    for (int i = 0; i < matrix.getHeight(); i++){
        for (int j = 0; j < matrix.getWidth(); j++){
            if (i == j) (*this)[i][j] = { matrix[i, j], -1};
            else (*this)[i][j] = { matrix[i, j] };
        }
    }
}

const Polynomial &PolynomialMatrix::operator[](int i, int j) const{
    int targetX = -1, targetY = -1;
    while (i >= 0){
        if(rows[++targetY]) i--;
    }
    while (j >= 0){
        if(cols[++targetX]) j--;
    }
    return (*this)[targetY][targetX];
}

Polynomial PolynomialMatrix::recursiveDet(int size){
    if (size == 2){
        return (*this)[0, 0] * (*this)[1, 1] - (*this)[1, 0] * (*this)[0, 1];
    }

    Polynomial res;
    int rowEliminated = this->size - size;
    rows[rowEliminated] = false;

    for (int i = 0; i < size; i++){
        if (!cols[i]) continue;

        cols[i] = false;
        auto a = (*this)[rowEliminated][i] * recursiveDet(size - 1) * ((rowEliminated + i) & 1 ? -1 : 1);
        res += a;
        cols[i] = true;
    }

    rows[rowEliminated] = true;
    return res;
}

Polynomial PolynomialMatrix::det() const{
    return const_cast<PolynomialMatrix *>(this)->recursiveDet(this->size);
}

Matrix PolynomialMatrix::evaluate(double x) const{
    Matrix mat(this->size, this->size);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            mat[i, j] = (*this)[i][j].evaluate(x);
        }
    }
    return mat;
}
