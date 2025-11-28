#include <string>
#include "dimensionmismatchexception.h"

DimensionMismatchException::DimensionMismatchException(int expected, int actural, std::string name){
    this->expected = expected;
    this->actural = actural;
    this->name = name;

    this->message = ("Expected " + name + " to be "
                   + std::to_string(expected) + ", found"
                   +  std::to_string(actural));
}

const char *DimensionMismatchException::what() const throw (){
    return this->message.c_str();
}
