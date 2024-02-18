/* MAP YOUR TECHNOLOGY SPECIFIC GATES */

#pragma once

#include <string>
#include <unordered_map>

const std::unordered_map<std::string, std::string> keywordMap = {
    {"AND2X1", "HS65_GS_AND2x4"},
    {"OR2X1", "HS65_GS_OR2x4"},
    {"Y=", "Z="},
    {"NAND2X1", "HS65_GS_NAND2x4"},
    {"NOR2X1", "HS65_GS_NOR2x4"},
    {"INVX1", "HS65_GS_IVX9"}
    // Add more mappings as needed
};
