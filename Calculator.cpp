#include "Calculator.h"
#include <stdexcept>

Calculator::Calculator(double l, double r) : lnum(l), rnum(r) {}

void Calculator::setNumbers(double l, double r) {
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
