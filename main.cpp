#include "tokenizer.cpp"
#include <cstdio>
#include <iostream>
#include <ostream>

using namespace std;
using namespace blif2verilog;

int main(int argc, char *argv[]) {
  cout << "simple parser start " << endl;

  FILE *fh = fopen("dualRail.blif", "r");
  if (!fh) {
    cerr << "Couldn't open file for some reason" << endl;
  }

  fseek(fh, 0, SEEK_END);
  size_t file_size = ftell(fh);

  fseek(fh, 0, SEEK_SET);

  string fileContents(file_size, ' ');
  fread(fileContents.data(), 1, file_size, fh);

  cout << fileContents << endl;

  Tokenizer tokenizer;
  vector<Token> tokens = tokenizer.parse(fileContents);

  for (Token currToken : tokens) {
    currToken.debugPrint();
  }

  return 0;
}
