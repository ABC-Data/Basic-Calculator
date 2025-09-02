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
    std::stack<char> operators;
    std::istringstream iss(expr);
    char token;
    bool expectNumber = true; // For tracking if a number/operator is expected next. (true = number, false = operator).

    // Loop through input from user
    while (iss >> token) {
        // If digit or decimal
        if (isdigit(token) || token == '.') {
            if (!expectNumber) {
                throw std::runtime_error("Invalid syntax: numbers without operator");
            }
            iss.putback(token);
            double value;
            iss >> value;
            values.push(value);
            expectNumber = false;
        }

        // If open bracket
        else if (token == '(') {
            if (!expectNumber) {
                throw std::runtime_error("Invalid syntax: missing operator before '('");
            }
            operators.push(token);
            expectNumber = true;
        }
        // check for close bracket
        else if (token == ')') {
            if (expectNumber) {
                throw std::runtime_error("Invalid syntax: empty parentheses or missing value");
            }
            // Calculate everthing within brackets 1st.
            while (!operators.empty() && operators.top() != '(') {
                if (values.size() < 2) throw std::runtime_error("Invalid syntax: missing operand");
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (operators.empty()) {
                throw std::runtime_error("Unbalanced parentheses: extra ')'");
            }
            operators.pop(); // Remove '('
            expectNumber = false;
        }

        // If operator
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            if (expectNumber) {
                throw std::runtime_error("Invalid syntax: operator without left operand");
            }
            while (!operators.empty() && operators.top() != '(' && precedence(operators.top()) >= precedence(token)) {
                if (values.size() < 2) throw std::runtime_error("Invalid syntax: missing operand");
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOp(val1, val2, op));
            }
            operators.push(token);
            expectNumber = true; 
        }
        else {
            throw std::runtime_error(std::string("Invalid character in expression: '") + token + "'");
        }
    }

    if (expectNumber) {
        throw std::runtime_error("Invalid syntax: expression ends with an operator");
    }

    while (!operators.empty()) {
        if (operators.top() == '(') throw std::runtime_error("Unbalanced parentheses: missing ')'");
        if (values.size() < 2) throw std::runtime_error("Invalid syntax: missing operand");
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(applyOp(val1, val2, op));
    }

    if (values.size() != 1) {
        throw std::runtime_error("Invalid syntax: unexpected error");
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
    std::cout << "Enter expression (e.g., 3+4 or (5-4)/2) or 'exit' to quit.\n";

    while (true) {
        std::cout << "\nInput: ";
        std::getline(std::cin, input);
        
        if (toLowerCase(input) == "exit") break;

        try {
            double result = evaluateExpression(input);
            std::cout << "= " << result << "\n";
        }
        catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }
    }
    return 0;
}