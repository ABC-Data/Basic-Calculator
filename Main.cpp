#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <algorithm>
#include "Calculator.h"

// Function to get operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to apply operator on 2 values
double applyOp(double l, double r, char op) {
    Calculator calc(l, r);
    switch (op) {
        case '+':
            return calc.add();
        case '-':
            return calc.subtract();
        case '*':
            return calc.multiply();
        case '/':
            return calc.divide();
        default:
            throw std::runtime_error("Invalid operator!");
    }
}

// Organise calculation based on operator precendence using Shunting Yard Algorithm
double evaluateExpression(const std::string& expr) {
    std::stack<double> values;
    std::stack<char> ops;
    std::istringstream iss(expr);
    char token;

    while (iss >> token) {
        if (isdigit(token) || token == '.') {
            iss.putback(token);
            double value;
            iss >> value;
            values.push(value);
        }
        else if (token == '(') {
            ops.push(token);
        }
        else if (token == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty()) ops.pop(); // Remove '('
        }
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(token);
        }
        else {
            throw std::runtime_error("Invalid character in expression!");
        }
    }

    // Apply remaining operators
    while (!ops.empty()) {
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

// Turn string into lower-case
std::string toLowerCase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return str;
}

int main() {
    std::string input;
    std::cout << "=== Calculator ===\n";
    std::cout << "Enter expression (e.g., 3+4 or 6*8) or 'exit' to quit.\n";

    while (true) {
        std::cout << "\nInput: ";
        std::getline(std::cin, input);
        
        if (toLowerCase(input) == "exit") break;

        try {
            double result = evaluateExpression(input);
            std::cout << "= " << result << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}