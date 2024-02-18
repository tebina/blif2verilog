/* MAP YOUR TECHNOLOGY SPECIFIC GATES */

#pragma once

#include <unordered_map>
#include <string>

const std::unordered_map<std::string, std::string> keywordMap = {
        {"AND2X1", "MY_AND2X1"},
        {"OR2X1", "MY_OR2X1"},
        {"NAND2X1", "MY_NAND2X1"}
        // Add more mappings as needed
};

