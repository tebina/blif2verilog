#include "parser.hpp"
#include "blifDefinition.hpp"
#include <iostream>
#include <optional>
#include <vector>

using namespace std;

tuple<bool, simpleParser::modelDefinition> simpleParser::Parser::expectModelDefinition() {

    auto parseStart = mCurrentToken;
    optional<tokenize::Token> possibleOperator = expectOperator(".");
    modelDefinition modelName;
    if (possibleOperator.has_value()) { // Operator found !
        optional<tokenize::Token> possibleIdentifier =
                expectIdentifier("model");
        if (possibleIdentifier.has_value()) {
            optional<tokenize::Token> possibleModelName = expectIdentifier();
            if (possibleModelName.has_value()) {
                modelName.mName = possibleModelName->mText;
                //cout << "We have a model name: " << modelName.mName << endl;
                return std::make_tuple(true, modelName);

            } else {
                mCurrentToken = parseStart;
            }
        } else {
            mCurrentToken = parseStart;
        }
    }
    return std::make_tuple(false, modelName);
}

tuple<bool, vector<simpleParser::ioDefinition>> simpleParser::Parser::expectInputsDefinition() {
    auto parseStart = mCurrentToken;
    vector<ioDefinition> inputsVector;
    optional<tokenize::Token> possibleOperator = expectOperator(".");
    if (possibleOperator.has_value()) {
        optional<tokenize::Token> possibleIdentifier =
                expectIdentifier("inputs");
        if (possibleIdentifier.has_value()) {
            while (!expectOperator(".")) {
                ioDefinition input;
                optional<tokenize::Token> possibleVariableName = expectIdentifier();
                if (possibleVariableName.has_value()) {
                    input.mName = possibleVariableName->mText;
                    inputsVector.push_back(input);
                }
                if (expectOperator(".")) {
                    --mCurrentToken;
                    break;
                }
            }

            return std::make_tuple(true, inputsVector);
        } else {
            mCurrentToken = parseStart;
        }
    } else {
        mCurrentToken = parseStart;
    }

    return std::make_tuple(false, inputsVector);
}

tuple<bool, vector<simpleParser::ioDefinition>> simpleParser::Parser::expectOutputsDefinition() {
    auto parseStart = mCurrentToken;
    vector<ioDefinition> outputsVector;
    optional<tokenize::Token> possibleOperator = expectOperator(".");
    if (possibleOperator.has_value()) { // Operator found !
        optional<tokenize::Token> possibleIdentifier =
                expectIdentifier("outputs");
        if (possibleIdentifier.has_value()) {
            while (!expectOperator(".")) {
                optional<tokenize::Token> possibleVariableName = expectIdentifier();
                if (possibleVariableName.has_value()) {
                    ioDefinition output;
                    output.mName = possibleVariableName->mText;
                    outputsVector.push_back(output);
                }
                if (expectOperator(".")) {
                    --mCurrentToken;
                    break;
                }
            }
            return std::make_tuple(true, outputsVector);
        } else {
            mCurrentToken = parseStart;
        }
    } else {
        mCurrentToken = parseStart;
    }

    return std::make_tuple(false, outputsVector);
}


tuple<bool, simpleParser::gateDefinition> simpleParser::Parser::expectGateDefinition() {
    auto parseStart = mCurrentToken;
    gateDefinition gate;
    optional<tokenize::Token> possibleDotOperator = expectOperator(".");
    if (possibleDotOperator.has_value()) { // Operator found !
        optional<tokenize::Token> possibleGateIdentifier =
                expectIdentifier("gate");
        if (possibleGateIdentifier.has_value()) {
            optional<tokenize::Token> possibleModelName = expectIdentifier();
            if (possibleModelName.has_value()) {
                gate.mName = possibleModelName->mText;
                while (!expectOperator(".")) {
                    gateNetsDefinition nets;
                    optional<tokenize::Token> possibleIdentifier = expectIdentifier();
                    if (possibleIdentifier.has_value()) {
                        optional<tokenize::Token> possibleOperator = expectOperator("=");
                        if (possibleOperator.has_value()) {
                            optional<tokenize::Token> possibleNetName = expectIdentifier();
                            if (possibleNetName.has_value()) {
                                nets.mName = possibleIdentifier->mText;
                                nets.mPin = possibleNetName->mText;
                                gate.mPins.push_back(nets);
                            }
                        }
                    }
                    if (expectOperator(".")) {
                        --mCurrentToken;
                        break;
                    }
                }
                return std::make_tuple(true, gate);
            } else {
                mCurrentToken = parseStart;
            }
        } else {
            mCurrentToken = parseStart;
        }
    }
    return std::make_tuple(false, gate);
}

bool simpleParser::Parser::expectEndModule() {
    auto parseStart = mCurrentToken;
    optional<tokenize::Token> possibleOperator = expectOperator(".");
    if (possibleOperator.has_value()) { // Operator found !
        optional<tokenize::Token> possibleIdentifier =
                expectIdentifier("end");
        if (possibleIdentifier.has_value()) {
            return true;
        } else {
            mCurrentToken = parseStart;
        }
    } else {
        mCurrentToken = parseStart;
    }
    return false;
}


void simpleParser::Parser::parse(vector<tokenize::Token> &tokens) {
    mEndToken = tokens.end();
    mCurrentToken = tokens.begin();
    netlistDefiniton netlistObject;


    while (mCurrentToken != mEndToken) {
        auto [foundModel, modelObj] = expectModelDefinition();
        auto [foundInput, inputObj] = expectInputsDefinition();
        auto [foundOutput, outputObj] = expectOutputsDefinition();
        auto [foundGate, gateObj] = expectGateDefinition();

        if (foundModel) {
            netlistObject.modelName = modelObj;
        }
        if (foundInput) {
            netlistObject.inputs = inputObj;
        }
        if (foundOutput) {
            netlistObject.outputs = outputObj;
        }
        if (foundGate) {
            netlistObject.gates.push_back(gateObj);
        }
        if (expectEndModule()) {
            //cout << "reached end of module ! " << endl;
            //break; // Exit the loop when end of module is reached
        }

        if (!foundModel && !foundInput && !foundOutput && !foundGate && !expectEndModule()){
            // Handle unknown identifier
            cerr << "Unknown identifier " << mCurrentToken->mText << endl;
            ++mCurrentToken;
        }
    }
    cout << "Found model name : " << netlistObject.modelName.mName << endl;
    cout << "The lenght of inputs vector is : " << netlistObject.inputs.size() << endl;
    cout << "The lenght of outputs vector is : " << netlistObject.outputs.size() << endl;

    cout << "Found the following inputs : ";
    for (auto &input: netlistObject.inputs) {
        cout << input.mName << " ";
    }
    cout << endl;

    cout << "Found the following outputs : ";
    for (auto &output: netlistObject.outputs) {
        cout << output.mName << " ";
    }
    cout << endl;

    cout << "Found the following gates : " << endl;
    for (auto &gate: netlistObject.gates) {
        cout << "found gate : " << gate.mName << " ";
        cout << "with the following nets : ";
        for (auto &mPin: gate.mPins) {
            cout << mPin.mName << " = " << mPin.mPin << " ";
        }
        cout << endl;
    }
    cout << endl;
}

optional<tokenize::Token> simpleParser::Parser::expectIdentifier(const string &name) {
    if (mCurrentToken == mEndToken) { return nullopt; }
    if (mCurrentToken->mType != tokenize::IDENTIFIER) { return nullopt; }
    if (!name.empty() && mCurrentToken->mText != name) { return nullopt; }

    tokenize::Token returnToken = *mCurrentToken;
    ++mCurrentToken;
    return returnToken;
}

optional<tokenize::Token> simpleParser::Parser::expectOperator(const string &name) {
    if (mCurrentToken == mEndToken) {
        return nullopt;
    }
    if (mCurrentToken->mType != tokenize::OPERATOR) {
        return nullopt;
    }
    if (name.empty() || mCurrentToken->mText != name) {
        return nullopt;
    }

    tokenize::Token returnToken = *mCurrentToken;
    ++mCurrentToken;
    return returnToken;
}
