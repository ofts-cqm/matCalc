#include "token.h"
#include "binaryoperatortoken.h"
#include "calculator.h"

Token::Token(OperatorToken *parent): parent(parent){};

bool finalizeToken(Token *lastInput, std::unique_ptr<Token> &&generated){
    if (lastInput->type() == TokenType::Number){
        OperatorToken *grandParent = lastInput->parent;
        std::unique_ptr<BinaryOperatorToken> parent = std::make_unique<BinaryOperatorToken>(std::move(lastInput->parent->right), *BinaryOperatorToken::multiply);
        parent->parent = grandParent;
        parent->right = std::move(generated);
        lastToken = parent->right.get();
        parent->right->parent = parent.get();
        grandParent->right = std::move(parent);
        return true;
    }else if (lastInput->type() == TokenType::Operator || lastInput->type() == TokenType::Root){
        generated->parent = static_cast<OperatorToken *>(lastInput);
        lastToken = generated.get();
        static_cast<OperatorToken *>(lastInput)->right = std::move(generated);
        return true;
    }

    logError("Unknown Number Pattern", input);
    return false;
}

Logger Token::logger;
