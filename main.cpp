#include "parser.hpp"
#include "tokenizer.hpp"
#include "codeGenerator.hpp"

#include <cstdio>
#include <iostream>
#include <memory>
#include <ostream>
#include <memory>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Blif Parser Start :" << endl;

    FILE *fh = fopen("../example2.blif", "r");
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

    codeGenerator::generateVerilog(netlist_ptr);

//    Jinja2CppLight::Template mytemplate( R"d(
//        This is my {{avalue}} template.  It's {{secondvalue}}...
//        Today's weather is {{weather}}.
//    )d" );
//    mytemplate.setValue( "avalue", 3 );
//    mytemplate.setValue( "secondvalue", 12.123f );
//    mytemplate.setValue( "weather", "rain" );
//    string result = mytemplate.render();
//    cout << result << endl;

}
