#include <iostream>
#include <string>
#include "mappings.hpp"
#include <regex>


class KeywordReplacer {
public:
    static void replaceKeywords(std::string* input) {
        // Check if input pointer is valid
        if (input == nullptr) {
            std::cerr << "Error: Null pointer passed to replaceKeywords" << std::endl;
            return;
        }

        std::string& output = *input;

        // Iterate through each mapping and replace keywords
        for (const auto& mapping : keywordMap) {
            std::regex pattern("\\b" + mapping.first + "\\b"); // Add word boundaries
            output = std::regex_replace(output, pattern, mapping.second);
        }
    }
};