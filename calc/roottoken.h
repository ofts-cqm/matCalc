#ifndef ROOTTOKEN_H
#define ROOTTOKEN_H

#include "token.h"
#include "operatortoken.h"

class RootToken : public OperatorToken
{
public:
    RootToken();

    RootToken(RootToken &&other);

    virtual TokenType type() const override;
};

#endif // ROOTTOKEN_H
