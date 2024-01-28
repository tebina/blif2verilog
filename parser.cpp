#include "parser.hpp"
#include "tokenizer.hpp"
#include <iostream>
#include <optional>
#include <vector>

using namespace simpleParser;
using namespace std;

bool Parser::expectModelDefinition() {
  optional<blif2verilog::Token> possibleOperator = expectOperator(".");
  if (possibleOperator.has_value()) { // Operator found !
    optional<blif2verilog::Token> possibleIdentifier =
        expectIdentifier("model");
    if (possibleIdentifier.has_value()) {
      cout << "We have a model : " << possibleIdentifier->mText << endl;
      return true;
    } else {
      --mCurrentToken;
    }
  } else {
    --mCurrentToken;
  }
  return false;
}

bool Parser::expectInputsDefinition() {
  optional<blif2verilog::Token> possibleOperator = expectOperator(".");
  if (possibleOperator.has_value()) { // Operator found !
    optional<blif2verilog::Token> possibleIdentifier =
        expectIdentifier("inputs");
    if (possibleIdentifier.has_value()) {
      cout << "We have inputs : " << possibleIdentifier->mText << endl;
      return true;
    } else {
      --mCurrentToken;
    }
  } else {
    --mCurrentToken;
  }
  return false;
}

bool Parser::expectOutputsDefinition() {
  optional<blif2verilog::Token> possibleOperator = expectOperator(".");
  if (possibleOperator.has_value()) { // Operator found !
    optional<blif2verilog::Token> possibleIdentifier =
        expectIdentifier("outputs");
    if (possibleIdentifier.has_value()) {
      cout << "We have outputs : " << possibleIdentifier->mText << endl;
      return true;
    } else {
      --mCurrentToken;
    }
  } else {
    --mCurrentToken;
  }
  return false;
}

void Parser::parse(vector<blif2verilog::Token> &tokens) {
  mEndToken = tokens.end();
  mCurrentToken = tokens.begin();

  while (mCurrentToken != mEndToken) {
    if (expectModelDefinition()) {
    } else {
      cerr << "Uknown identifier " << mCurrentToken->mText << "." << endl;
      ++mCurrentToken;
    }

    if (expectInputsDefinition()) {
    } else {
      cerr << "Uknown identifier " << mCurrentToken->mText << "." << endl;
      ++mCurrentToken;
    }

    if (expectOutputsDefinition()) {
    } else {
      cerr << "Uknown identifier " << mCurrentToken->mText << "." << endl;
      ++mCurrentToken;
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

optional<Type> Parser::expectType() {
  optional<blif2verilog::Token> possibleType = expectIdentifier();
  if (!possibleType) {
    return nullopt;
  }

  map<string, Type>::iterator foundType = mTypes.find(possibleType->mText);
  if (foundType == mTypes.end()) {
    //--mCurrentToken;
    return nullopt;
  }

  return foundType->second;
}
