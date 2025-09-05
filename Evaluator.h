#pragma once
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <cmath>
#include <regex>
#include "Operation.h"

class Evaluator {
public:
    Evaluator();

    /* Public Functions */
    double evaluate(const std::vector<std::string>& tokens);

private:
    /* Private Functions */
    int precedence(const std::string& op) const;
    double applyOperation(const std::string& op, double lhs, double rhs) const;

    /* Private Variables */
    std::map<std::string, std::unique_ptr<Operation>> operations;
};

