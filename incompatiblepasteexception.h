#ifndef INCOMPATIBLEPASTEEXCEPTION_H
#define INCOMPATIBLEPASTEEXCEPTION_H

#include "abstractnumberpane.h"
#include "genericnumber.h"
#include <exception>
class IncompatiblePasteException : public std::exception
{
public:
    IncompatiblePasteException(NumberType original, NumberType clipboard);

    IncompatiblePasteException(const AbstractNumberPane &original, const GenericNumber &clipboard);

    virtual const char* what() const throw();

private:
    NumberType original, clipboard;
    std::string message;
};

#endif // INCOMPATIBLEPASTEEXCEPTION_H
