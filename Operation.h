#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include <memory>
#include <stdexcept>

class Operation {
public:
    virtual ~Operation() = default;
    virtual double apply(double lhs, double rhs) const = 0;
    virtual std::string symbol() const = 0;
};

// Addition
class AddOperation : public Operation {
public:
    double apply(double lhs, double rhs) const override {
        return lhs + rhs;
    }
    std::string symbol() const override { return "+"; }
};

// Subtraction
class SubtractOperation : public Operation {
public:
    double apply(double lhs, double rhs) const override {
        return lhs - rhs;
    }
    std::string symbol() const override { return "-"; }
};

// Multiplication
class MultiplyOperation : public Operation {
public:
    double apply(double lhs, double rhs) const override {
        return lhs * rhs;
    }
    std::string symbol() const override { return "*"; }
};

// Division
class DivideOperation : public Operation {
public:
    double apply(double lhs, double rhs) const override {
        if (rhs == 0) throw std::runtime_error("Division by zero");
        return lhs / rhs;
    }
    std::string symbol() const override { return "/"; }
};

// Exponential
class PowerOperation : public Operation {
public:
    double apply(double lhs, double rhs) const override {
        if (lhs == 0 && rhs == 0)
            throw std::runtime_error("0^0 is undefined");
        return std::pow(lhs, rhs);
    }
    std::string symbol() const override { return "^"; }
};

// Square Root
class SqrtOperation : public Operation {
public:
    double apply(double lhs, double rhs) const override {
        if (lhs < 0) throw std::runtime_error("Square root of negative number");
        return std::sqrt(lhs);
    }
    std::string symbol() const override { return "sqrt"; }
};

#endif