#ifndef DIMENSIONMISMATCHEXCEPTION_H
#define DIMENSIONMISMATCHEXCEPTION_H

#include <exception>
#include <string>

class DimensionMismatchException : public std::exception{

public:
    DimensionMismatchException(int expected, int actural, std::string name = "dimension");

    const char* what() const noexcept override;

private:
    int expected;
    int actural;
    std::string name;
    std::string message;
};


#endif // DIMENSIONMISMATCHEXCEPTION_H
