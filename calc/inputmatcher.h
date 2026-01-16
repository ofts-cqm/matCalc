#ifndef INPUTMATCHER_H
#define INPUTMATCHER_H

#include <stack>
#include <string>

class InputMatcher
{
public:
    InputMatcher(const std::string &expression);

    bool isEnd() const;

    bool isClear() const;

    void trim();

    void skip(int length);

    std::string get(int length, bool allowPartial = false, int preview = 0) const;

    std::pair<int, int> getLastRequestCutOff() const;

    bool match(const std::string &str, bool matchCase = true);

    void push();

    void pop();

    void ignore();

    int getIndex() const;

private:
    std::string expression_base;
    std::string_view expression;
    std::stack<int> positionStack;
    int index = 0, length;
};

#endif // INPUTMATCHER_H
