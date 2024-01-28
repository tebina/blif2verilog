#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace blif2verilog {

using namespace std;

enum TokenType {
  WHITESPACE,
  IDENTIFIER,
  INTEGER_LITERAL,
  STRING_LITERAL,
  OPERATOR,
  COMMENT,
  STRING_ESCAPE_SEQUENCE
};

static const char *sTokenTypeStrings[] = {
    "WHITESPACE", "IDENTIFIER", "INTEGER_LITERAL",       "STRING_LITERAL",
    "OPERATOR",   "COMMENT",    "STRING_ESCAPE_SEQUENCE"};

class Token {
public:
  enum TokenType mType { WHITESPACE };
  string mText{0};
  size_t mLineNumber{0};

  void debugPrint() const;

private:
};

class Tokenizer {
public:
  vector<Token> parse(const string &inProgram);

private:
  void endToken(Token &token, vector<Token> &tokens);
};

} // namespace blif2verilog
