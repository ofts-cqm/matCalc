#include "roottoken.h"

RootToken::RootToken()
    : OperatorToken(114514, "", [](double d){return d;}) {}


TokenType RootToken::type() const{
    return TokenType::Root;
}
