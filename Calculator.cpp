#include "Calculator.h"
#include <stdexcept>

Calculator::Calculator(double r, double l) : num1(r), num2(l) {}

void Calculator::setNumbers(double r, double l) {
    lnum = l;
    rnum = r;
}

double Calculator::add() const {
    return lnum + rnum;
}

double Calculator::subtract() const {
    return lnum - rnum;
}

double Calculator::multiply() const {
    return lnum * rnum;
}

double Calculator::divide() const {
    if (rnum == 0) {
        throw std::runtime_error("Error: Division by zero!");
    }
    return lnum / rnum;
}
