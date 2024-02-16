#include "codeGenerator.hpp"
#include <iostream>

using namespace std;

void codeGenerator::generateVerilog(std::unique_ptr<simpleParser::netlistDefiniton> &netlist_ptr) {


    std::vector<std::string> netNames;
    for (auto &gate  : netlist_ptr->gates){
        for (auto &net : gate.mPins) {
                netNames.push_back(net.mPin);


        }
    }

    cout << "module " << netlist_ptr->modelName.mName << "( ";
    for (auto & input : netlist_ptr->inputs){
            cout << input.mName << ", " ;
    }

    cout << endl;

    for (int output=0; output < netlist_ptr->outputs.size(); output++){
        if (output == netlist_ptr->outputs.size()-1) {
            cout << netlist_ptr->outputs[output].mName << ");";
        } else {
            cout << netlist_ptr->outputs[output].mName << ", " ;
        }
    }

    cout << endl;

    cout << "input ";
    for (int input=0; input < netlist_ptr->inputs.size(); input++){
        if (input == netlist_ptr->inputs.size()-1) {
            cout << netlist_ptr->inputs[input].mName << ";";
        } else {
            cout << netlist_ptr->inputs[input].mName << ", " ;
        }
    }

    cout << endl;

    cout << "output ";
    for (int output=0; output < netlist_ptr->outputs.size(); output++){
        if (output == netlist_ptr->outputs.size()-1) {
            cout << netlist_ptr->outputs[output].mName << ";";
        } else {
            cout << netlist_ptr->outputs[output].mName << ", " ;
        }
    }

    cout << endl;

    cout << "wire ";
    for (int net=0; net < netNames.size(); net++){
        if (net == netNames.size()-1) {
            cout << netNames[net] << ";";
        } else {
            cout << netNames[net] << ",";
        }
    }

    cout << endl;

    int instance_cnt = 0;
    for (auto &gate : netlist_ptr->gates){
        cout << gate.mName << " ";
        cout << "instance_number" << instance_cnt << " (";
        for (int i = 0 ; i < gate.mPins.size(); i++){
            if (i == gate.mPins.size()-1){
                cout << "." << gate.mPins[i].mName <<"(" << gate.mPins[i].mPin << ")";
            }else {
                cout << "." << gate.mPins[i].mName <<"(" << gate.mPins[i].mPin << "),";
            }
        }
        instance_cnt++;
        cout << ");" << endl;
    }
    cout << "endmodule" << endl;
}
