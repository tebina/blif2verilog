#pragma once
#include "tokenizer.hpp"
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace simpleParser {

using namespace std;

enum BUILTIN_KEYWORDS { MODEL, INPUTS, OUTPUTS, GATE, END };

class Type {
public:
  Type(const string &name = "", enum BUILTIN_KEYWORDS type = MODEL)
      : mName(name), mType(type){};
  string mName;
  enum BUILTIN_KEYWORDS mType;
  vector<Type> mField;
};

class Parser {
public:
  Parser();
  void parse(vector<blif2verilog::Token> &tokens);

private:
  optional<Type> expectType();
  optional<blif2verilog::Token> expectIdentifier(const string &name = string());
  optional<blif2verilog::Token> expectOperator(const string &name = string());
  vector<blif2verilog::Token>::iterator mCurrentToken;
  vector<blif2verilog::Token>::iterator mEndToken;
  map<string, Type> mTypes;
};

} // namespace simpleParser
