#include "token.h"
#include "binaryoperatortoken.h"
#include "calculator.h"

Token::Token(OperatorToken *parent): parent(parent){};

Token::Token(){}

Token *finalizeToken(Token *lastInput, Token *generated){
    if (lastInput->type() == TokenType::Number){
        OperatorToken *parent = lastInput->parent;
        BinaryOperatorToken *token = new BinaryOperatorToken(lastInput, *BinaryOperatorToken::multiply);
        token->right = generated;
        token->parent = parent;
        generated->parent = token;
        parent->right = token;
        return token;
    } else if (lastInput->type() == TokenType::Operator || lastInput->type() == TokenType::Root){
        OperatorToken *input = static_cast<OperatorToken *>(lastInput);
        generated->parent = input;
        input->right = generated;
        return generated;
    }
    logError("Error: Token After Parenthesis Without Operators", input);
    return generated;
}
