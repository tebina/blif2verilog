#pragma once

#include <cstddef>
#include <string>
#include <vector>


namespace tokenize {

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
  std::string mText;
  size_t mLineNumber{0};

  void debugPrint() const;

private:
};

class Tokenizer {
public:
  static std::vector<Token> parse(const std::string &inProgram);

private:
  static void endToken(Token &token, std::vector<Token> &tokens);
};

} // namespace tokenize
