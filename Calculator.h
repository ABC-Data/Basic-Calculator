#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>
#include <utility>

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

	// Helper Functions
	std::vector<std::string> tokenize(const std::string& expr);
	void validateTokens(const std::vector<std::string>& tokens);
	double evaluateTokens(const std::vector<std::string>& tokens);
	double applyOp(double l, double r, char op);
	int precedence(char op);

	/* Private Variables */
	std::vector<std::pair<std::string, double>> history;
};

#endif
