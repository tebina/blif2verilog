#include "codeGenerator.hpp"
#include <iostream>

using namespace std;

string codeGenerator::generateVerilog(std::unique_ptr<simpleParser::netlistDefiniton> &netlist_ptr) {
    std::string verilogText;
    std::vector<std::string> netNames;

    for (auto &gate  : netlist_ptr->gates){
        for (auto &net : gate.mPins) {
                netNames.push_back(net.mPin);


        }
    }

    verilogText += "module " + netlist_ptr->modelName.mName + "( ";
    cout << "module " << netlist_ptr->modelName.mName << "( ";
    for (auto & input : netlist_ptr->inputs){
            cout << input.mName << ", " ;
            verilogText += input.mName + ", " ;
    }

    cout << endl;
    verilogText += "\n";

    for (int output=0; output < netlist_ptr->outputs.size(); output++){
        if (output == netlist_ptr->outputs.size()-1) {
            cout << netlist_ptr->outputs[output].mName << ");";
            verilogText += netlist_ptr->outputs[output].mName + ");";
        } else {
            cout << netlist_ptr->outputs[output].mName << ", " ;
            verilogText += netlist_ptr->outputs[output].mName + ", " ;
        }
    }

    cout << endl;
    verilogText += "\n";

    cout << "input ";
    verilogText += "input ";

    for (int input=0; input < netlist_ptr->inputs.size(); input++){
        if (input == netlist_ptr->inputs.size()-1) {
            cout << netlist_ptr->inputs[input].mName << ";";
            verilogText += netlist_ptr->inputs[input].mName + ";";
        } else {
            cout << netlist_ptr->inputs[input].mName << ", " ;
            verilogText +=  netlist_ptr->inputs[input].mName + ", " ;
        }
    }

    cout << endl;
    verilogText += "\n";

    cout << "output ";
    verilogText += "output ";
    for (int output=0; output < netlist_ptr->outputs.size(); output++){
        if (output == netlist_ptr->outputs.size()-1) {
            cout << netlist_ptr->outputs[output].mName << ";";
            verilogText += netlist_ptr->outputs[output].mName + ";";
        } else {
            cout << netlist_ptr->outputs[output].mName << ", " ;
            verilogText += netlist_ptr->outputs[output].mName + ", " ;
        }
    }

    cout << endl;
    verilogText += "\n";

    cout << "wire ";
    verilogText += "wire ";
    for (int net=0; net < netNames.size(); net++){
        if (net == netNames.size()-1) {
            cout << netNames[net] << ";";
            verilogText +=  netNames[net] + ";";
        } else {
            cout << netNames[net] << ",";
            verilogText += netNames[net] + ",";
        }
    }

    cout << endl;
    verilogText += "\n";

    int instance_cnt = 0;
    for (auto &gate : netlist_ptr->gates){
        cout << gate.mName << " ";
        verilogText += gate.mName + " ";
        cout << "instance_number" << instance_cnt << " (";
        verilogText += "instance_number" + to_string(instance_cnt) + " (";
        for (int i = 0 ; i < gate.mPins.size(); i++){
            if (i == gate.mPins.size()-1){
                cout << "." << gate.mPins[i].mName <<"(" << gate.mPins[i].mPin << ")";
                verilogText += "." + gate.mPins[i].mName +"(" + gate.mPins[i].mPin + ")";

            }else {
                cout << "." << gate.mPins[i].mName <<"(" << gate.mPins[i].mPin << "),";
                verilogText += "." + gate.mPins[i].mName  + "(" + gate.mPins[i].mPin + "),";
            }
        }
        instance_cnt++;
        cout << ");" << endl;
        verilogText +=  ");";
        verilogText += "\n";

    }
    cout << "endmodule" << endl;
    verilogText += "endmodule";
    verilogText +=  "\n";
    return verilogText;
}
