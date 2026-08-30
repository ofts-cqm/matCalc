#include "calculator.h"
#include "roottoken.h"
#include "binaryoperatortoken.h"
#include "parenthesistoken.h"
#include "numbertoken.h"
#include <memory>
#include <sstream>
#include <vector>

namespace Calculator{

    namespace {
        std::vector<std::unique_ptr<Token>> registeredTokens;
        std::ostringstream error_message;
        std::string first_error;
        int errorCount = 0;
    }

    std::optional<double> evaluate(const std::string& expression, const bool record_result){
        errorCount = 0;
        input = InputMatcher(expression);
        error_message = std::ostringstream();
        auto root = std::make_unique<RootToken>();
        lastToken = root.get();

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

        if (errorCount != 0) abort = true;
        if (abort) return {};

        if (debugMode){
            root->debug();
        }

        double result = root->evaluate();
        if (result < 1e-10 && result > -1e-10) result = 0;
        if (record_result) previousAnswer = result;

        return result;
    }

    bool matchNext(InputMatcher &input, Token *lastInput){
        for (const auto &token : registeredTokens){
            if(token->parse(input, lastInput))
                return true;
        }
        return false;
    }

    static void logError(const std::string& error, const InputMatcher &context){
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
    Token *lastToken = nullptr;

    void init(){
        if (!registeredTokens.empty()) return;
        OperatorToken::init(registeredTokens);
        BinaryOperatorToken::init(registeredTokens);
        registeredTokens.push_back(std::make_unique<NumberToken>(0, nullptr));
        RootToken root;
        registeredTokens.push_back(std::make_unique<ParenthesisToken>(root, nullptr));
    }
}
