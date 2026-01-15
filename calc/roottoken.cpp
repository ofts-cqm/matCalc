#include "roottoken.h"

RootToken::RootToken()
    : OperatorToken(114514, "Root Token", [](double d){return d;}) {}


RootToken::RootToken(RootToken &&other)
    : RootToken(){
    this->right = std::move(other.right);
}

TokenType RootToken::type() const{
    return TokenType::Root;
}
