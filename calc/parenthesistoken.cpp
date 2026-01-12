#include "parenthesistoken.h"

ParenthesisToken::ParenthesisToken(RootToken &content, Token *parent)
    : Token(dynamic_cast<OperatorToken *>(parent)), content(content){}

double ParenthesisToken::evaluate() const{
    return content.evaluate();
}

Token *ParenthesisToken::parse(InputMatcher &input, Token *lastInput) const{
    input.push();
    if (!input.match("(")){
        input.pop();
        return nullptr;
    }

    RootToken root;
    Token *matched = matchNext(input, &root);
    root.right = matched;

    if (matched == nullptr){
        logError("Error: Nothing In Parentheses", input);
        input.pop();
        return nullptr;
    }

    while (!input.match(")")){
        matched = matchNext(input, &root);
        if (matched == nullptr){
            logError("Error: Nothing In Parentheses", input);
            input.pop();
            return nullptr;
        }
    }

    input.ignore();
    return finalizeToken(lastInput, lastToken = new ParenthesisToken(root, lastInput));
}

void ParenthesisToken::debug() const{
    content.debug();
}

TokenType ParenthesisToken::type() const{
    return TokenType::Parenthesis;
}
