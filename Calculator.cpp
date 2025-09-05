#include "Calculator.h"
#include <stack>
#include <sstream>
#include <regex>
#include <stdexcept>
#include <iostream>
#include <cmath>

Calculator::Calculator() {

}

Calculator::~Calculator() {
    history.clear();
}


double Calculator::evaluate(const std::string& expression) {
    std::vector<std::string> tokens = tokenizer.tokenize(expression);
    tokenizer.validateTokens(tokens);
    double result = evaluator.evaluate(tokens);
    history.add(expression, result);
    return result;
}

void Calculator::printHistory() const {
    history.print();
}
