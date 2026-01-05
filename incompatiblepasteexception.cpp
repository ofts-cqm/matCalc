#include "incompatiblepasteexception.h"
#include "util.h"

IncompatiblePasteException::IncompatiblePasteException(NumberType original, NumberType clipboard)
    : original(original), clipboard(clipboard) {
    this->message = "Cannot Paste " + nameForNumberType(clipboard) + " onto " + nameForNumberType(original) + "!";
}

IncompatiblePasteException::IncompatiblePasteException(const AbstractNumberPane &original, const GenericNumber &clipboard):
    IncompatiblePasteException(original.getType(), clipboard.getType()) {}

const char *IncompatiblePasteException::what() const throw() {
    return this->message.c_str();
}
