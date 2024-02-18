#include "parser.hpp"
#include "tokenizer.hpp"
#include "codeGenerator.hpp"
#include "preprocess.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <memory>
#include <ostream>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        cerr << "Usage: " << "./blif2verilog" << " file.blif [generated.v]" << endl;
        return 1;
    }

    const char* blifFileName = argv[1];
    const char* verilogFileName = (argc == 3) ? argv[2] : "generated.v";

    cout << "Blif Parser Start..." << endl;

    FILE *fh = fopen(blifFileName, "r");
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


    KeywordReplacer::replaceKeywords(&fileContents); //Preprocessor to replace gates to desired namings


    vector<tokenize::Token> tokens = tokenize::Tokenizer::parse(fileContents);

    //uncomment to print all tokens
//  for (const tokenize::Token& currToken : tokens) {
//    currToken.debugPrint();
//  }

    // instantiate netlist_object and convert it into a unique pointer for usage
    simpleParser::netlistDefiniton netlist_object;
    simpleParser::Parser parser;
    netlist_object = parser.parse(tokens);

    // Define the NetlistPtr type alias for std::unique_ptr<simpleParser::netlistDefiniton>
    using NetlistPtr = std::unique_ptr<simpleParser::netlistDefiniton>;
    // Declare a unique pointer to hold the netlist object
    NetlistPtr netlist_ptr;
    // Assign the netlist object to the unique pointer
    netlist_ptr = std::make_unique<simpleParser::netlistDefiniton>(netlist_object);


    std::string verilogText = codeGenerator::generateVerilog(netlist_ptr);



    // Write Verilog text to a file
    std::ofstream outputFile(verilogFileName);
    if (outputFile.is_open()) {
        outputFile << verilogText;
        outputFile.close();
        std::cout << "Verilog file generated successfully!\n";
    } else {
        std::cerr << "Unable to open file " << verilogFileName << " for writing!\n";
        return 1;
    }
    return 0;
}
