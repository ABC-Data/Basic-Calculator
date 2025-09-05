#pragma once
#include <string>
#include <vector>

class Tokenizer {
public:
    /* Public Functions */
    std::vector<std::string> tokenize(const std::string& expr);
    void validateTokens(const std::vector<std::string>& tokens);
};