#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
class Logger
{
public:
    Logger();

    Logger &start();

    Logger &finish();

    Logger &write(const std::string &str, bool isLast = false);

private:
    int indentation;
    std::vector<bool> indentationRules;
};



#endif // LOGGER_H
