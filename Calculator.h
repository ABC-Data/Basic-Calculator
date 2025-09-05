#ifndef CALCULATOR_H
#define CALCULATOR_H

#pragma once
#include <string>
#include <vector>
#include <utility>
#include "History.h"
#include "Tokenizer.h"

class Calculator {
public:
	Calculator();
	~Calculator();

	/* Public Functions */
	double evaluate(const std::string& expr);
	void printHistory() const;

private:
	/* Private Functions */
	// Base Operation Functions
	double add(double l, double r) const;
	double subtract(double l, double r) const;
	double multiply(double l, double r) const;
	double divide(double l, double r) const;
	double power(double l, double r);
	double squareRoot(double a);

	// Helper Functions
	double evaluateTokens(const std::vector<std::string>& tokens);
	double applyOp(double l, double r, char op);
	int precedence(char op);
	bool isFunction(const std::string& token);

	/* Private Variables */
	History history;
	Tokenizer tokenizer;
};

#endif
