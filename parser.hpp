#pragma once
#include "tokenizer.hpp"
#include <map>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace simpleParser {

enum BUILTIN_KEYWORDS { MODEL, INPUTS, OUTPUTS, GATE, END };

class Type {
public:
  explicit Type(std::string name = "", enum BUILTIN_KEYWORDS type = MODEL)
      : mName(std::move(name)), mType(type){};
  std::string mName;
  enum BUILTIN_KEYWORDS mType;
  std::vector<Type> mField;
};

class Parser {
public:
  Parser();
  void parse(std::vector<tokenize::Token> &tokens);

private:
    [[maybe_unused]] std::optional<Type> expectType();
  bool expectModelDefinition();
  bool expectInputsDefinition();
  bool expectOutputsDefinition();
  std::optional<tokenize::Token> expectIdentifier(const std::string &name = std::string());
  std::optional<tokenize::Token> expectOperator(const std::string &name = std::string());
  std::vector<tokenize::Token>::iterator mCurrentToken;
  std::vector<tokenize::Token>::iterator mEndToken;
  std::map<std::string, Type> mTypes;
};

} // namespace simpleParser
