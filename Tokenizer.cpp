#include "Tokenizer.h"
#include <cctype>
#include <stdexcept>
#include <regex>

// Tokenize input into numbers, operators, parentheses, negative numbers
std::vector<std::string> Tokenizer::tokenize(const std::string& expr) {
    std::vector<std::string> tokens;
    std::string num;
    bool expectNumber = true;

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        if (isspace(c)) {
            if (!num.empty()) {
                tokens.push_back(num);
                num.clear();
            }
            continue;
        }

        if (isdigit(c) || c == '.') {
            num += c;
            expectNumber = false;
        }
        else if (c == '-' && expectNumber) { // unary minus
            num += c;
        }
        else {
            if (!num.empty()) {
                tokens.push_back(num);
                num.clear();
            }

            if (expr.substr(i, 4) == "sqrt") {
                tokens.push_back("sqrt");
                i += 3;
                expectNumber = true;
            }
            else if (c == '(' || c == ')' || c == '+' || c == '*' || c == '/' || c == '^' || c == '-') {
                tokens.push_back(std::string(1, c));
                expectNumber = (c != ')');
            }
            else {
                throw std::runtime_error(std::string("Invalid character: ") + c);
            }
        }
    }

    if (!num.empty()) tokens.push_back(num);
    return tokens;
}

// Check tokens for error-handling
void Tokenizer::validateTokens(const std::vector<std::string>& tokens) {
    if (tokens.empty()) throw std::runtime_error("Empty expression");

    int balance = 0;
    bool expectNumberOrFunction = true;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& t = tokens[i];

        if (t == "(") {
            balance++;
            expectNumberOrFunction = true;
        }
        else if (t == ")") {
            balance--;
            if (balance < 0) throw std::runtime_error("Mismatched parentheses");
            expectNumberOrFunction = false;
        }
        else if (t == "sqrt") {
            if (!expectNumberOrFunction) throw std::runtime_error("Invalid sqrt placement");
            expectNumberOrFunction = true;
        }
        else if (std::regex_match(t, std::regex(R"(-?\d+(\.\d+)?)"))) {
            if (!expectNumberOrFunction)
                throw std::runtime_error("Two numbers without operator");
            expectNumberOrFunction = false;
        }
        else if (t == "+" || t == "-" || t == "*" || t == "/" || t == "^") {
            if (expectNumberOrFunction)
                throw std::runtime_error("Operator in invalid position");
            expectNumberOrFunction = true;
        }
        else {
            throw std::runtime_error("Invalid token: " + t);
        }
    }

    if (balance != 0) throw std::runtime_error("Unbalanced parentheses");
    if (expectNumberOrFunction) throw std::runtime_error("Expression ends with operator or incomplete function");
}


