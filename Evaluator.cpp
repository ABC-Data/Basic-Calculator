#include "Evaluator.h"
#include <stdexcept>
#include <iostream>

Evaluator::Evaluator() {
    operations["+"] = std::make_unique<AddOperation>();
    operations["-"] = std::make_unique<SubtractOperation>();
    operations["*"] = std::make_unique<MultiplyOperation>();
    operations["/"] = std::make_unique<DivideOperation>();
    operations["^"] = std::make_unique<PowerOperation>();
    operations["sqrt"] = std::make_unique<SqrtOperation>();
}

int Evaluator::precedence(const std::string& op) const {
    if (op == "sqrt") return 4;
    if (op == "^")    return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

double Evaluator::applyOperation(const std::string& op, double lhs, double rhs) const {
    auto it = operations.find(op);
    if (it == operations.end())
        throw std::runtime_error("Unknown operator: " + op);
    return it->second->apply(lhs, rhs);
}

double Evaluator::evaluate(const std::vector<std::string>& tokens) {
    std::stack<double> values;
    std::stack<std::string> ops;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& t = tokens[i];

        // Number
        if (std::regex_match(t, std::regex(R"(-?\d+(\.\d+)?)"))) {
            values.push(std::stod(t));
        }
        // Opening parenthesis
        else if (t == "(") {
            ops.push(t);
        }
        // Closing parenthesis
        else if (t == ")") {
            while (!ops.empty() && ops.top() != "(") {
                std::string op = ops.top(); ops.pop();
                double rhs = values.top(); values.pop();
                double lhs = values.top(); values.pop();
                values.push(applyOperation(op, lhs, rhs));
            }
            if (!ops.empty()) ops.pop(); // pop "("
        }
        // Operator
        else if (operations.find(t) != operations.end()) {
            while (!ops.empty() && precedence(ops.top()) >= precedence(t)) {
                std::string op = ops.top(); ops.pop();

                if (op == "sqrt") { // unary
                    if (values.empty()) 
                        throw std::runtime_error("Not enough operands for sqrt");
                    double lhs = values.top(); values.pop();
                    values.push(applyOperation(op, lhs, 0));
                }
                else { // binary
                    if (values.size() < 2) 
                        throw std::runtime_error("Not enough operands");
                    double rhs = values.top(); values.pop();
                    double lhs = values.top(); values.pop();
                    values.push(applyOperation(op, lhs, rhs));
                }
            }
            ops.push(t);
        }
        else {
            throw std::runtime_error("Invalid token: " + t);
        }
    }

    while (!ops.empty()) {
        std::string op = ops.top(); ops.pop();
        if (op == "sqrt") {
            if (values.empty()) 
                throw std::runtime_error("Not enough operands for sqrt");
            double lhs = values.top(); values.pop();
            values.push(applyOperation(op, lhs, 0));
        }
        else {
            if (values.size() < 2) 
                throw std::runtime_error("Not enough operands");
            double rhs = values.top(); values.pop();
            double lhs = values.top(); values.pop();
            values.push(applyOperation(op, lhs, rhs));
        }
    }

    if (values.size() != 1)
        throw std::runtime_error("Evaluation error");

    return values.top();
}
