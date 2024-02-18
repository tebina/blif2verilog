#pragma once
#include "blifDefinition.hpp"
#include <memory>
#include <string>

class codeGenerator {
public:
    static std::string generateVerilog(std::unique_ptr<simpleParser::netlistDefiniton>& netlist_ptr);

};
