#include "Calculator.h"
#include <stack>
#include <sstream>
#include <regex>
#include <stdexcept>
#include <iostream>

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

// Function to get operator precedence
int Calculator::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
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
    default: throw std::runtime_error("Invalid operator!");
    }
}

// Tokenize input into numbers, operators, parentheses, negative numbers
std::vector<std::string> Calculator::tokenize(const std::string& expr) {
    std::vector<std::string> tokens;
    std::string num;
    bool expectNumber = true;

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (isspace(c)) continue;

        if (isdigit(c) || c == '.') {
            num += c;
            expectNumber = false;
        }
        else if (c == '-' && expectNumber) {
            num += c;
        }
        else {
            if (!num.empty()) {
                tokens.push_back(num);
                num.clear();
            }
            if (c == '(' || c == ')' || c == '+' || c == '*' || c == '/') {
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
            expectNumber = (c != ')');
        }
    }

    if (!num.empty()) tokens.push_back(num);
    return tokens;
}

// Check tokens for error-handling
void Calculator::validateTokens(const std::vector<std::string>& tokens) {
    if (tokens.empty()) throw std::runtime_error("Empty expression");

    int parenBalance = 0;
    bool expectNumber = true;

    for (const auto& t : tokens) {
        if (t == "(") {
            parenBalance++;
            expectNumber = true;
        }
        else if (t == ")") {
            if (parenBalance == 0 || expectNumber)
                throw std::runtime_error("Invalid parentheses or empty brackets");
            parenBalance--;
            expectNumber = false;
        }
        else if (std::regex_match(t, std::regex(R"(-?\d+(\.\d+)?)"))) {
            if (!expectNumber)
                throw std::runtime_error("Two numbers without operator");
            expectNumber = false;
        }
        else if (t == "+" || t == "-" || t == "*" || t == "/") {
            if (expectNumber)
                throw std::runtime_error("Operator without left operand");
            expectNumber = true;
        }
        else {
            throw std::runtime_error("Invalid token: " + t);
        }
    }

    if (parenBalance != 0) throw std::runtime_error("Unbalanced parentheses");
    if (expectNumber) throw std::runtime_error("Expression ends with an operator");
}

// Calculate tokens based on operator precendence using Shunting Yard Algorithm
double Calculator::evaluateTokens(const std::vector<std::string>& tokens) {
    std::stack<double> values;
    std::stack<char> ops;

    for (const auto& t : tokens) {
        if (std::regex_match(t, std::regex(R"(-?\d+(\.\d+)?)"))) {
            values.push(std::stod(t));
        }
        else if (t == "(") {
            ops.push('(');
        }
        else if (t == ")") {
            while (!ops.empty() && ops.top() != '(') {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty()) ops.pop(); // remove '('
        }
        else { // operator
            char op = t[0];
            while (!ops.empty() && ops.top() != '(' && precedence(ops.top()) >= precedence(op)) {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op2 = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op2));
            }
            ops.push(op);
        }
    }

    while (!ops.empty()) {
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

double Calculator::evaluate(const std::string& expr) {
    std::vector<std::string> tokens = tokenize(expr);
    validateTokens(tokens);
    double result = evaluateTokens(tokens);
    history.push_back({ expr, result });
    return result;
}

void Calculator::printHistory() const {
    if (history.empty()) {
        std::cout << "No previous history.\n";
        return;
    }
    int i = 1;
    for (const auto& entry : history) {
        std::cout << i++ << ") " << entry.first << " = " << entry.second << "\n";
    }
}
