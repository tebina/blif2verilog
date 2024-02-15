#include "parser.hpp"
#include "tokenizer.hpp"
#include <cstdio>
#include <iostream>
#include <ostream>

using namespace std;

int main(int argc, char *argv[]) {
  cout << "Blif Parser Start :" << endl;

  FILE *fh = fopen("../example.blif", "r");
  if (!fh) {
    cerr << "Couldn't open file for some reason" << endl;
  }

  fseek(fh, 0, SEEK_END);
  size_t file_size = ftell(fh);

  fseek(fh, 0, SEEK_SET);

  string fileContents(file_size, ' ');
  fread(fileContents.data(), 1, file_size, fh);

  //Uncomment to pring file contents
  //cout << fileContents << endl;

  //tokenize::Tokenizer tokenizer;
  vector<tokenize::Token> tokens = tokenize::Tokenizer::parse(fileContents);

  //uncomment to print all tokens
//  for (const tokenize::Token& currToken : tokens) {
//    currToken.debugPrint();
//  }
  simpleParser::Parser parser;
  parser.parse(tokens);

}
