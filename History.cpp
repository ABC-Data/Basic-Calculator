#include "History.h"

void History::add(const std::string& expr, double result) {
    records.emplace_back(expr, result);
}

void History::print() const {
    if (records.empty()) {
        std::cout << "No previous history.\n";
        return;
    }
    int i = 1;
    for (const auto& entry : records) {
        std::cout << i++ << ") " << entry.first << " = " << entry.second << "\n";
    }
}

void History::clear() {
    records.clear();
}