#include <iostream>
#include <algorithm>
#include "Calculator.h"

// Turn string into lower-case
std::string toLowerCase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return str;
}

int main() {
    Calculator calc;
    std::string input;

    std::cout << "=== Calculator ===\n";
    std::cout << "Supports +, -, *, /, parentheses, negative numbers\n";
    std::cout << "Enter expression (e.g., 3+4 or (5-4)/2) or 'exit' to quit\n";

    while (true) {
        std::cout << "\nInput: ";
        std::getline(std::cin, input);
        if (input.empty()) continue;
        if (toLowerCase(input) == "exit") break;
        if (toLowerCase(input) == "history") {
            calc.printHistory();
            continue;
        }

        try {
            double result = calc.evaluate(input);
            std::cout << "= " << result << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
