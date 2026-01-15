#include "logger.h"
#include <iostream>

Logger::Logger():indentation(0) {}

Logger &Logger::start(){
    indentation++;
    indentationRules.push_back(true);
    return *this;
}

Logger &Logger::finish(){
    indentation--;
    indentationRules.pop_back();
    return *this;
}

Logger &Logger::write(const std::string &str, bool isLast){
    for (int i = 0; i < indentationRules.size() - 1; i++){
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
