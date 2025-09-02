#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>

class Calculator {
public:
	Calculator(double l = 0, double r = 0);
	~Calculator();

	void setNumbers(double l, double r);
	double add() const;
	double subtract() const;
	double multiply() const;
	double divide() const;

private:
	double lnum, rnum;
};

#endif
