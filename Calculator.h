#ifndef CALCULATOR_H
#define CALCULATOR_H

#pragma once
#include <string>
#include <vector>
#include <utility>
#include "History.h"
#include "Tokenizer.h"
#include "Evaluator.h"

class Calculator {
public:
	Calculator();
	~Calculator();

	/* Public Functions */
	double evaluate(const std::string& expr);
	void printHistory() const;

private:
	/* Private Functions */


	/* Private Variables */
	History history;
	Tokenizer tokenizer;
	Evaluator evaluator;
};

#endif
