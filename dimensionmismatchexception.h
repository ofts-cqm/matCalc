#ifndef DIMENSIONMISMATCHEXCEPTION_H
#define DIMENSIONMISMATCHEXCEPTION_H

#include <exception>
#include <string>

class DimensionMismatchException : public std::exception{

public:
    DimensionMismatchException(int expected, int actural, std::string name = "dimension");

    virtual const char* what() const throw();

private:
    int expected;
    int actural;
    std::string name;
    std::string message;
};


#endif // DIMENSIONMISMATCHEXCEPTION_H
