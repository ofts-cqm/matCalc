#include "logger.h"
#include <iostream>

Logger::Logger():indentation(0) {}

Logger &Logger::start(){
    indentation++;
    indentationRules.push_back(true);
    return *this;
}

Logger &Logger::finish(){
    if (indentationRules.empty()) return *this;
    indentation--;
    indentationRules.pop_back();
    return *this;
}

Logger &Logger::write(const std::string &str, bool isLast){
    if (indentationRules.empty()) {
        std::cout << str << std::endl;
        return *this;
    }
    for (std::size_t i = 0; i + 1 < indentationRules.size(); i++){
        std::cout << (indentationRules[i] ? "│  " : "   ");
    }

    if (isLast){
        indentationRules[indentation - 1] = false;
        std::cout << "└  ";
    }else{
        std::cout << "├  ";
    }

    std::cout << str << std::endl;
    return *this;
}
