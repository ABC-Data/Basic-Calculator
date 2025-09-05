#pragma once
#include <string>
#include <vector>
#include <iostream>

class History {
public:
    void add(const std::string& expr, double result);
    void print() const;
    void clear();

private:
    std::vector<std::pair<std::string, double>> records;
};