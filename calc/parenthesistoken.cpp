#include "parenthesistoken.h"

ParenthesisToken::ParenthesisToken(RootToken &content, Token *parent)
    : Token(dynamic_cast<OperatorToken *>(parent)), content(std::move(content)){

}

double ParenthesisToken::evaluate() const{
    return content.evaluate();
}

bool ParenthesisToken::parse(InputMatcher &input, Token *lastInput) const{
    if (!input.match("(")) return false;

    input.push();
    RootToken root;
    lastToken = &root;

    while (!input.match(")")){
        if(!matchNext(input, lastToken)){
            logError("Error: Parenthesis Not Closed!", input);
            input.pop();
            return false;
        }
    }

    if (root.right == nullptr){
        logError("Error: Parenthesis Is Empty", input);
        input.pop();
        return false;
    }

    input.ignore();
    return finalizeToken(lastInput, std::make_unique<ParenthesisToken>(root, lastInput));
}

void ParenthesisToken::debug() const{
    content.debug();
}

TokenType ParenthesisToken::type() const{
    return TokenType::Parenthesis;
}
