#include "parser.hpp"
#include "tokenizer.hpp"
#include <iostream>
#include <optional>
#include <vector>

using namespace simpleParser;
using namespace std;

void Parser::parse(vector<blif2verilog::Token> &tokens) {
  mEndToken = tokens.end();
  mCurrentToken = tokens.begin();

  while (mCurrentToken != tokens.end()) {
    optional<blif2verilog::Token> possibleOperator = expectOperator(".");
    if (possibleOperator.has_value()) { // Operator found !
      optional<blif2verilog::Token> possibleName = expectIdentifier();
      if (possibleName.has_value()) { // Function found !
        cout << "We have a function : " << possibleName->mText << ".";
        exit(0);
      }
    }
  }
}

optional<blif2verilog::Token> Parser::expectIdentifier(const string &name) {
  if (mCurrentToken == mEndToken) {
    return nullopt;
  }
  if (mCurrentToken->mType != blif2verilog::IDENTIFIER) {
    return nullopt;
  }
  if (name.empty() || mCurrentToken->mText != name) {
    return nullopt;
  }

  blif2verilog::Token returnToken = *mCurrentToken;
  ++mCurrentToken;
  return returnToken;
}

optional<blif2verilog::Token> Parser::expectOperator(const string &name) {
  if (mCurrentToken == mEndToken) {
    return nullopt;
  }
  if (mCurrentToken->mType != blif2verilog::OPERATOR) {
    return nullopt;
  }
  if (name.empty() || mCurrentToken->mText != name) {
    return nullopt;
  }

  blif2verilog::Token returnToken = *mCurrentToken;
  ++mCurrentToken;
  return returnToken;
}

Parser::Parser() {
  mTypes["model"] = Type("model", MODEL);
  mTypes["inputs"] = Type("inputs", INPUTS);
  mTypes["outputs"] = Type("outputs", OUTPUTS);
  mTypes["gate"] = Type("gate", GATE);
  mTypes["end"] = Type("end", END);
}
