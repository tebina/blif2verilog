#pragma once

#include "tokenizer.hpp"
#include "Type.hpp"
#include "blifDefinition.hpp"

#include <map>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace simpleParser {

    class Parser {
    public:
        Parser();

        void parse(std::vector<tokenize::Token> &tokens);

    private:
        [[maybe_unused]] std::optional<Type> expectType();

        bool expectModelDefinition();

        bool expectInputsDefinition();

        bool expectOutputsDefinition();

        //bool expectGateNetsDefinition();

        bool expectGateDefinition();

        bool expectEndModule();

        std::optional<tokenize::Token> expectIdentifier(const std::string &name = std::string());

        std::optional<tokenize::Token> expectOperator(const std::string &name = std::string());


        std::vector<tokenize::Token>::iterator mCurrentToken;
        std::vector<tokenize::Token>::iterator mEndToken;
        std::map<std::string, Type> mTypes;

    };

} // namespace simpleParser
