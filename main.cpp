#include "parser.hpp"
#include "tokenizer.hpp"
#include <cstdio>
#include <iostream>
#include <ostream>

using namespace std;

int main(int argc, char *argv[]) {
  cout << "simple parser start " << endl;

  FILE *fh = fopen("C:\\Users\\tebin\\CLionProjects\\blif2verilog\\example.blif", "r");
  if (!fh) {
    cerr << "Couldn't open file for some reason" << endl;
  }

  fseek(fh, 0, SEEK_END);
  size_t file_size = ftell(fh);

  fseek(fh, 0, SEEK_SET);

  string fileContents(file_size, ' ');
  fread(fileContents.data(), 1, file_size, fh);

  cout << fileContents << endl;

  //tokenize::Tokenizer tokenizer;
  vector<tokenize::Token> tokens = tokenize::Tokenizer::parse(fileContents);

  for (const tokenize::Token& currToken : tokens) {
    currToken.debugPrint();
  }
  simpleParser::Parser parser;
  parser.parse(tokens);

  return 0;
}
