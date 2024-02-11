#include "tokenizer.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>



using namespace std;

vector<tokenize::Token> tokenize::Tokenizer::parse(const string &inProgram) {
  vector<Token> tokens;
  Token currentToken;
  currentToken.mLineNumber = 1;

  for (char currCh : inProgram) {
    if (currentToken.mType == STRING_ESCAPE_SEQUENCE) {
      switch (currCh) {
      case 'n':
        currentToken.mText.append(1, '\n');
        break;
      case 't':
        currentToken.mText.append(1, '\t');
        break;
      case 'r':
        currentToken.mText.append(1, '\r');
        break;
      case '\\':
        currentToken.mText.append(1, '\\');
        break;
      default:
        throw runtime_error(string("Unknown escape sequence: \\") +
                            string(1, currCh) + " in string on line" +
                            to_string(currentToken.mLineNumber) + ".");
      }
      currentToken.mType = STRING_LITERAL;
      continue;
    }
  }

  for (char currCh : inProgram) {
    switch (currCh) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      if (currentToken.mType == WHITESPACE) {
        currentToken.mType = INTEGER_LITERAL;
        currentToken.mText.append(1, currCh);
      } else {
        currentToken.mText.append(1, currCh);
      }
      break;
    case '=':
    case ':':
    case ';':
    case '.':
      if (currentToken.mType != STRING_LITERAL) {
        endToken(currentToken, tokens);
        currentToken.mType = OPERATOR;
        currentToken.mText.append(1, currCh);
        endToken(currentToken, tokens);
      } else {
        currentToken.mText.append(1, currCh);
      }
      break;
    case ' ':
    case '\t':
      endToken(currentToken, tokens);
      ++currentToken.mLineNumber;
      break;
    case '\r':
    case '\n':
      endToken(currentToken, tokens);
      ++currentToken.mLineNumber;
      break;
    case '"':
      if (currentToken.mType != STRING_LITERAL) {
        endToken(currentToken, tokens);
        currentToken.mType = STRING_LITERAL;
        currentToken.mText.append(1, currCh);
      } else {
          endToken(currentToken, tokens);
      }
      break;
    case '\\':
      if (currentToken.mType == STRING_LITERAL) {
        currentToken.mType = STRING_ESCAPE_SEQUENCE;
        currentToken.mText.append(1, currCh);
      } else {
        endToken(currentToken, tokens);
        currentToken.mType = OPERATOR;
        currentToken.mText.append(1, currCh);
        endToken(currentToken, tokens);
      }
      break;
    case '#':
      if (currentToken.mType == STRING_LITERAL) {
        endToken(currentToken, tokens);
        currentToken.mType = COMMENT;
        currentToken.mText.append(1, currCh);
      } else {
        endToken(currentToken, tokens);
      }
      break;
    default:
      if (currentToken.mType == WHITESPACE ||
          currentToken.mType == INTEGER_LITERAL) {
        endToken(currentToken, tokens);
        currentToken.mType = IDENTIFIER;
        currentToken.mText.append(1, currCh);
      } else {
        currentToken.mText.append(1, currCh);
      }
      break;
    }
  }
  endToken(currentToken, tokens);
  return tokens;
}

void tokenize::Tokenizer::endToken(Token &token, vector<Token> &tokens) {
  if (token.mType == COMMENT) {
    cout << "Comment found " << token.mText << endl;
  }

  if (token.mType != WHITESPACE) {
    tokens.push_back(token);
  }
  token.mType = WHITESPACE;
  token.mText.erase();
}

void tokenize::Token::debugPrint() const {
  cout << "Token(" << sTokenTypeStrings[mType] << ", \"" << mText << "\", "
       << mLineNumber << ")" << endl;
}
