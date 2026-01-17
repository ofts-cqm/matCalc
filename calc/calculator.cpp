#include "calculator.h"
#include "roottoken.h"
#include "binaryoperatortoken.h"
#include "parenthesistoken.h"
#include "numbertoken.h"
#include <vector>

namespace Calculator{

    std::vector<Token *> registeredTokens;

    std::optional<double> evaluate(std::string expression, bool record_result){
        errorCount = 0;
        input = InputMatcher(expression);
        error_message = std::ostringstream();
        RootToken *root = new RootToken();
        lastToken = root;

        while (matchNext(input, lastToken)){}



        OperatorToken *temp;
        bool abort = false;
        if (!input.isEnd()) {
            logError("Error: Some Expressions Are Not Evaluated!", input);
            abort = true;
        }
        if (!input.isClear()) {
            logError("Internal Error: Some Internal Error Occurred!", input);
            abort = true;
        }
        if (root->right == nullptr) {
            logError("Error: Nothing Evaluated", input);
            abort = true;
        }
        if ((temp = dynamic_cast<OperatorToken *>(lastToken)) && temp->right == nullptr){
            logError("Error: Unfinished Token", input);
            abort = true;
        }

        if (abort) return {};

        if (debugMode){
            root->debug();
        }

        double result = root->evaluate();
        if (result < 1e-10 && result > -1e-10) result = 0;
        if (record_result) previousAnswer = result;

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
        if (errorCount == 0) first_error = error;

        error_message << error << '\n';
        error_message << "At Index = " << context.getIndex() << ":\n";
        error_message << context.get(10, false, 5) << "\n";
        auto [preview, length] = context.getLastRequestCutOff();
        for (int i = 0; i < 10; i++){
            if (preview == i) error_message << '^';
            else error_message << '.';
        }
        error_message << "\n\n";
        errorCount++;
    }

    std::string getShortErrorMessage(){
        if (errorCount == 0) return "";
        if (errorCount == 1) return first_error;
        return first_error + "( and " + std::to_string(errorCount - 1) + " more)";
    }

    std::string getLongErrorMessage() { return error_message.str(); }

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
}
