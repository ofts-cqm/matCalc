#ifndef INCOMPATIBLEPASTEEXCEPTION_H
#define INCOMPATIBLEPASTEEXCEPTION_H

#include "abstractnumberpane.h"
#include "../genericnumber.h"
#include <exception>
class IncompatiblePasteException : public std::exception
{
public:
    IncompatiblePasteException(NumberType original, NumberType clipboard);

    IncompatiblePasteException(const AbstractNumberPane &original, const GenericNumber &clipboard);

    const char* what() const noexcept override;

private:
    NumberType original, clipboard;
    std::string message;
};

#endif // INCOMPATIBLEPASTEEXCEPTION_H
