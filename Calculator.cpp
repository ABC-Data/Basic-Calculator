#include "Calculator.h"
#include <stack>
#include <sstream>
#include <regex>
#include <stdexcept>
#include <iostream>
#include <cmath>

Calculator::Calculator() {}

Calculator::~Calculator() {
    history.clear();
}

double Calculator::add(double l, double r) const {
    return l + r;
}

double Calculator::subtract(double l, double r) const {
    return l - r;
}

double Calculator::multiply(double l, double r) const {
    return l * r;
}

double Calculator::divide(double l, double r) const {
    if (r == 0) {
        throw std::runtime_error("Division by zero!");
    }
    return l / r;
}

double Calculator::power(double l, double r) {
    if (l == 0 && r == 0)
        throw std::runtime_error("0^0 is undefined");
    return std::pow(l, r);
}

double Calculator::squareRoot(double a) {
    if (a < 0) throw std::runtime_error("Cannot sqrt negative number");
    return std::sqrt(a);
}

// Check if a token is a function
bool Calculator::isFunction(const std::string& token) {
    return token == "sqrt";
}

// Function to get operator precedence
int Calculator::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to apply operator on 2 values
double Calculator::applyOp(double l, double r, char op) {
    switch (op) {
    case '+': 
        return add(l, r);
    case '-': 
        return subtract(l, r);
    case '*': 
        return multiply(l, r);
    case '/': 
        return divide(l, r);
    case '^': 
        return power(l, r);
    default: 
        throw std::runtime_error("Invalid operator!");
    }
}

// Tokenize input into numbers, operators, parentheses, negative numbers
std::vector<std::string> Calculator::tokenize(const std::string& expr) {
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

            // Check for sqrt
            if (expr.substr(i, 4) == "sqrt") {
                tokens.push_back("sqrt");
                i += 3;
                expectNumber = true;
            }
            else if (c == '(' || c == ')' || c == '+' || c == '*' || c == '/' || c == '^') {
                tokens.push_back(std::string(1, c));
                expectNumber = (c != ')');
            }
            else if (c == '-') {
                tokens.push_back(std::string(1, c));
                expectNumber = true;
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
void Calculator::validateTokens(const std::vector<std::string>& tokens) {
    if (tokens.empty()) throw std::runtime_error("Empty expression");

    int parenBalance = 0;
    bool expectNumberOrFunction = true;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& t = tokens[i];

        if (t == "(") {
            parenBalance++;
            expectNumberOrFunction = true;
        }
        else if (t == ")") {
            if (parenBalance == 0 || expectNumberOrFunction)
                throw std::runtime_error("Invalid parentheses or empty brackets");
            parenBalance--;
            expectNumberOrFunction = false;
        }
        else if (std::regex_match(t, std::regex(R"(-?\d+(\.\d+)?)"))) {
            if (!expectNumberOrFunction)
                throw std::runtime_error("Two numbers without operator");
            expectNumberOrFunction = false;
        }
        else if (t == "+" || t == "-" || t == "*" || t == "/" || t == "^") {
            if (expectNumberOrFunction)
                throw std::runtime_error("Operator without left operand");
            expectNumberOrFunction = true;
        }
        else if (isFunction(t)) {
            if (i + 1 >= tokens.size() || tokens[i + 1] != "(")
                throw std::runtime_error("Function must be followed by '('");
            expectNumberOrFunction = true;
        }
        else {
            throw std::runtime_error("Invalid token: " + t);
        }
    }

    if (parenBalance != 0) throw std::runtime_error("Unbalanced parentheses");
    if (expectNumberOrFunction) throw std::runtime_error("Expression ends with an operator or incomplete function");
}

// Calculate tokens based on operator precendence using Shunting Yard Algorithm
double Calculator::evaluateTokens(const std::vector<std::string>& tokens) {
    std::stack<double> values;
    std::stack<std::string> operators;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const std::string& t = tokens[i];

        if (std::regex_match(t, std::regex(R"(-?\d+(\.\d+)?)"))) {
            values.push(std::stod(t));
        }
        else if (isFunction(t)) {
            operators.push(t);
        }
        else if (t == "(") {
            operators.push(t);
        }
        else if (t == ")") {
            while (!operators.empty() && operators.top() != "(") {
                std::string op = operators.top(); operators.pop();
                if (isFunction(op)) {
                    double val = values.top(); values.pop();
                    values.push(squareRoot(val));
                }
                else {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    values.push(applyOp(val1, val2, op[0]));
                }
            }
            if (!operators.empty()) operators.pop(); // remove '('
        }
        else { // operator
            char op = t[0];
            while (!operators.empty() && operators.top() != "(" &&
                ((isFunction(operators.top())) || precedence(operators.top()[0]) >= precedence(op))) {
                std::string topOp = operators.top(); operators.pop();
                if (isFunction(topOp)) {
                    double val = values.top(); values.pop();
                    values.push(squareRoot(val));
                }
                else {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    values.push(applyOp(val1, val2, topOp[0]));
                }
            }
            operators.push(t);
        }
    }

    while (!operators.empty()) {
        std::string op = operators.top(); operators.pop();
        if (isFunction(op)) {
            double val = values.top(); values.pop();
            values.push(squareRoot(val));
        }
        else {
            double val2 = values.top(); values.pop();
            double val1 = values.top(); values.pop();
            values.push(applyOp(val1, val2, op[0]));
        }
    }

    return values.top();
}

double Calculator::evaluate(const std::string& expr) {
    std::vector<std::string> tokens = tokenize(expr);
    validateTokens(tokens);
    double result = evaluateTokens(tokens);
    history.add(expr, result);
    return result;
}

void Calculator::printHistory() const {
    history.print();
}
