#pragma once

#include "tokenizer.hpp"
#include "blifDefinition.hpp"

#include <map>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace simpleParser {

    class Parser {
    public:
        Parser()= default;

        simpleParser::netlistDefiniton parse(std::vector<tokenize::Token> &tokens);

    private:

        std::tuple<bool, simpleParser::modelDefinition> expectModelDefinition();

        std::tuple<bool, vector<simpleParser::ioDefinition>> expectInputsDefinition();

        std::tuple<bool, vector<simpleParser::ioDefinition>> expectOutputsDefinition();

        std::tuple<bool, simpleParser::gateDefinition> expectGateDefinition();

        bool expectEndModule();

        std::optional<tokenize::Token> expectIdentifier(const std::string &name = std::string());

        std::optional<tokenize::Token> expectOperator(const std::string &name = std::string());


        std::vector<tokenize::Token>::iterator mCurrentToken;
        std::vector<tokenize::Token>::iterator mEndToken;

    };

} // namespace simpleParser
