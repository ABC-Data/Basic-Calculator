#pragma once
#include <string>
#include <vector>
#include <iostream>

class History {
public:
    /* Public Functions */
    void add(const std::string& expr, double result);
    void print() const;
    void clear();

private:
    /* Private Functions */


    /* Private Variables */
    std::vector<std::pair<std::string, double>> records;
};