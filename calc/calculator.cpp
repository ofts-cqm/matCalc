#include "calculator.h"
#include "roottoken.h"
#include "binaryoperatortoken.h"
#include "parenthesistoken.h"
#include "numbertoken.h"
#include <vector>

std::vector<Token *> registeredTokens;

std::optional<double> evaluate(std::string expression, std::string &error, bool record_result){
    input = InputMatcher(expression);
    error_message = std::ostringstream();
    RootToken *root = new RootToken();
    lastToken = root;

    while (matchNext(input, lastToken)){}

    if (!input.isEnd()) logError("Error: Some Expressions Are Not Evaluated!", input);
    if (!input.isClear()) logError("Internal Error: Some Internal Error Occurred!", input);
    if (root->right == nullptr) logError("Error: Nothing Evaluated", input);

    if (debugMode){
        root->debug();
    }

    double result = root->evaluate();
    if (result < 1e-10 && result > -1e-10) result = 0;
    if (record_result) previousAnswer = result;
    error = error_message.str();

    delete root;
    return result;
}

bool matchNext(InputMatcher &input, Token *lastInput){
    for (const Token *token : registeredTokens){
        if(token->parse(input, lastInput))
            return true;
    }
    return false;
}

void logError(std::string error, const InputMatcher &context){
    error_message << "Error: " << error << '\n';
    error_message << "At Index = " << context.getIndex() << ":\n";
    error_message << context.get(10, true) << "\n\n";
}

bool radianMode = false;
bool debugMode = false;
double previousAnswer = 0;
InputMatcher input = InputMatcher("");
Token *lastToken;

void init(){
    OperatorToken::init(registeredTokens);
    BinaryOperatorToken::init(registeredTokens);
    registeredTokens.push_back(new NumberToken(0, nullptr));
    RootToken root;
    registeredTokens.push_back(new ParenthesisToken(root, nullptr));
}
