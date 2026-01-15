#include "inputmatcher.h"

InputMatcher::InputMatcher(const std::string &expression)
    : expression_base(expression), expression(), length(expression.length()) {
    this->expression = expression_base;
}

bool InputMatcher::isEnd() const {return index == length; };

bool InputMatcher::isClear() const {return positionStack.empty(); }

void InputMatcher::trim(){
    if (index == length) return;
    char current = expression[index];
    while(current == ' ' || current == '\n' || current == '\t' || current == '\r'){
        index ++;
        if (index == length) return;
        current = expression[index];
    }
}

void InputMatcher::skip(int length){
    if (index + length > this->length) throw std::out_of_range("Cannot skip length " + std::to_string(length) + " because it exceeds the total length");
    index += length;
    trim();
}

std::string InputMatcher::get(int length, bool allowPartial) const{
    if (index + length <= this->length) return expression_base.substr(index, length);
    return allowPartial ? expression_base.substr(index) : "";
}

bool compareIgnoreCase(const std::string_view& str1, const std::string& str2)
{
    if (str1.length() != str2.length())
        return false;

    for (int i = 0; i < str1.length(); ++i) {
        if (tolower(str1[i]) != tolower(str2[i]))
            return false;
    }

    return true;
}

bool InputMatcher::match(const std::string &str, bool matchCase){
    if (str.length() + index > this->length) return false;
    bool matched = matchCase ? expression_base.compare(index, str.length(), str) == 0
        : compareIgnoreCase(expression_base.substr(index, str.length()), str);

    if (matched) skip(str.length());
    return matched;
}

void InputMatcher::push(){
    positionStack.push(index);
}

void InputMatcher::pop() {
    index = positionStack.top();
    positionStack.pop();
}

void InputMatcher::ignore(){
    positionStack.pop();
}

int InputMatcher::getIndex() const{
    return index;
}

