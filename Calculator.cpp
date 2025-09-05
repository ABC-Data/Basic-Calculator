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
    std::vector<std::string> tokens = tokenizer.tokenize(expr);
    tokenizer.validateTokens(tokens);
    double result = evaluateTokens(tokens);
    history.add(expr, result);
    return result;
}

void Calculator::printHistory() const {
    history.print();
}
