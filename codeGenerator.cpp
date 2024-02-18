#include "codeGenerator.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

string codeGenerator::generateVerilog(std::unique_ptr<simpleParser::netlistDefiniton> &netlist_ptr) {
    std::string verilogText;
    std::vector<std::string> netNames;//wires
    std::vector<std::string> inputNames; //inputs buffer to filter them out from wires
    std::vector<std::string> outputNames;//outputs buffer to filter them out from wires

    std::vector<std::string> *inputsPtr = &inputNames;
    std::vector<std::string> *outputsPtr = &outputNames;

    for (auto &input: netlist_ptr->inputs) {
        inputNames.push_back(input.mName);
    }
    for (auto &output: netlist_ptr->inputs) {
        outputNames.push_back(output.mName);
    }

    for (const auto &gate: netlist_ptr->gates) {
        for (const auto &net: gate.mPins) {
            if (find(inputsPtr->begin(), inputsPtr->end(), net.mPin) == inputsPtr->end() &&
                find(outputsPtr->begin(), outputsPtr->end(), net.mPin) == outputsPtr->end()) {
                netNames.push_back(net.mPin);
            }
        }
    }

    verilogText += "// Generated blif2verilog module";
    verilogText +="\n";
    verilogText +="\n";
    verilogText += "module " + netlist_ptr->modelName.mName + "( ";
    //cout << "module " << netlist_ptr->modelName.mName << "( ";
    for (auto &input: netlist_ptr->inputs) {
        //cout << input.mName << ", " ;
        verilogText += input.mName + ", ";
    }

    //cout << endl;
    verilogText += "\n";

    for (int output = 0; output < netlist_ptr->outputs.size(); output++) {
        if (output == netlist_ptr->outputs.size() - 1) {
            //cout << netlist_ptr->outputs[output].mName << ");";
            verilogText += netlist_ptr->outputs[output].mName + ");";
        } else {
            //cout << netlist_ptr->outputs[output].mName << ", " ;
            verilogText += netlist_ptr->outputs[output].mName + ", ";
        }
    }

    //cout << endl;
    verilogText += "\n";
    verilogText += "\n";

    //cout << "input ";
    verilogText += "input ";
    for (int input = 0; input < netlist_ptr->inputs.size(); input++) {
            if (input % 8 == 0 && input != 0) {
                // Start a new line with "wire" keyword
                verilogText += "input ";
            }
        if (input % 8 == 7 || input == netlist_ptr->inputs.size() - 1) {
            // Last wire in the group or last wire overall
            verilogText += netlist_ptr->inputs[input].mName + ";\n"; // Add semicolon and newline
        } else {
            // Wire in the group but not the last one
            verilogText +=  netlist_ptr->inputs[input].mName + ", ";
        }
    }

    //cout << endl;
    verilogText += "\n";

    //cout << "output ";
    verilogText += "output ";
    for (int output = 0; output < netlist_ptr->outputs.size(); output++) {
        if (output % 8 == 0 && output != 0) {
            // Start a new line with "wire" keyword
            verilogText += "output ";
        }
        if (output % 8 == 7 || output == netlist_ptr->outputs.size() - 1) {
            // Last wire in the group or last wire overall
            verilogText += netlist_ptr->outputs[output].mName + ";\n"; // Add semicolon and newline
        } else {
            // Wire in the group but not the last one
            verilogText +=  netlist_ptr->outputs[output].mName + ", ";
        }
    }

    //cout << endl;
    verilogText += "\n";
    verilogText += "\n";

    //cout << "wire ";
    verilogText += "wire ";
    for (int net = 0; net < netNames.size(); net++) {
        if (net % 8 == 0 && net != 0) {
            // Start a new line with "wire" keyword
            verilogText += "wire ";
        }
        // Append the wire name
        if (net % 8 == 7 || net == netNames.size() - 1) {
            // Last wire in the group or last wire overall
            verilogText += netNames[net] + ";\n"; // Add semicolon and newline
        } else {
            // Wire in the group but not the last one
            verilogText += netNames[net] + ", ";
        }
    }

    //cout << endl;
    verilogText += "\n";

    int instance_cnt = 0;
    for (auto &gate: netlist_ptr->gates) {
        //cout << gate.mName << " ";
        verilogText += gate.mName + " ";
        //cout << "instance_number" << instance_cnt << " (";
        verilogText += "instance_number" + to_string(instance_cnt) + " (";
        for (int i = 0; i < gate.mPins.size(); i++) {
            if (i == gate.mPins.size() - 1) {
                //cout << "." << gate.mPins[i].mName <<"(" << gate.mPins[i].mPin << ")";
                verilogText += "." + gate.mPins[i].mName + "(" + gate.mPins[i].mPin + ")";

            } else {
                //cout << "." << gate.mPins[i].mName <<"(" << gate.mPins[i].mPin << "),";
                verilogText += "." + gate.mPins[i].mName + "(" + gate.mPins[i].mPin + "), ";
            }
        }
        instance_cnt++;
        //cout << ");" << endl;
        verilogText += ");";
        verilogText += "\n";

    }
    //cout << "endmodule" << endl;
    verilogText += "\n";
    verilogText += "endmodule";
    verilogText += "\n";
    return verilogText;
}
