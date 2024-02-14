#include "parser.hpp"
#include "blifDefinition.hpp"
#include <iostream>
#include <optional>
#include <vector>

using namespace std;

bool simpleParser::Parser::expectModelDefinition() {

    auto parseStart = mCurrentToken;
    optional<tokenize::Token> possibleOperator = expectOperator(".");
    if (possibleOperator.has_value()) { // Operator found !
        optional<tokenize::Token> possibleIdentifier =
                expectIdentifier("model");
        if (possibleIdentifier.has_value()) {
            optional<tokenize::Token> possibleModelName = expectIdentifier();
            if (possibleModelName.has_value()) {
                modelDefinition modelName;
                modelName.mName = possibleModelName->mText;
                //cout << "We have a model name: " << modelName.mName << endl;
                return true;

            } else {
                mCurrentToken = parseStart;
            }
        } else {
            mCurrentToken = parseStart;
        }
    }
    return false;
}

bool simpleParser::Parser::expectInputsDefinition() {
    auto parseStart = mCurrentToken;
    optional<tokenize::Token> possibleOperator = expectOperator(".");
    if (possibleOperator.has_value()) {
        optional<tokenize::Token> possibleIdentifier =
                expectIdentifier("inputs");
        if (possibleIdentifier.has_value()) {
            manyInputDefinition manyInputs;
            while (!expectOperator(".")) {
                inputDefinition input;
                optional<tokenize::Token> possibleVariableName = expectIdentifier();
                if (possibleVariableName.has_value()) {
                    input.mName = possibleVariableName->mText;
                    manyInputs.mName.push_back(input);
                    cout << input.mName << endl;
                }
                if (expectOperator(".")) {
                    --mCurrentToken;
                    break;
                }
            }
            return true;
        } else {
            mCurrentToken = parseStart;
        }
    } else {
        mCurrentToken = parseStart;
    }

    return false;
}

bool simpleParser::Parser::expectOutputsDefinition() {
    auto parseStart = mCurrentToken;
    optional<tokenize::Token> possibleOperator = expectOperator(".");
    if (possibleOperator.has_value()) { // Operator found !
        optional<tokenize::Token> possibleIdentifier =
                expectIdentifier("outputs");
        if (possibleIdentifier.has_value()) {
            manyOutputDefinition manyOutputs;
            while (!expectOperator(".")) {
                outputDefinition output;
                optional<tokenize::Token> possibleVariableName = expectIdentifier();
                if (possibleVariableName.has_value()) {
                    output.mName = possibleVariableName->mText;
                    manyOutputs.mName.push_back(output);
                    cout << output.mName << endl;
                }
                if (expectOperator(".")) {
                    --mCurrentToken;
                    break;
                }
            }
            //cout << "We have output name: " << possibleModelName->mText << endl;
            return true;
        } else {
            mCurrentToken = parseStart;
        }
    } else {
        mCurrentToken = parseStart;
    }

    return false;
}


bool simpleParser::Parser::expectGateDefinition() {
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
                cout << "found gate : " << gate.mName << ". ";
                cout << "with the following nets : ";
                for (auto &mPin: gate.mPins) {
                    cout << mPin.mName << " = " << mPin.mPin << " ";
                }
                cout << endl;
                return true;
            } else {
                mCurrentToken = parseStart;
            }
        } else {
            mCurrentToken = parseStart;
        }
    }
    return false;
}

bool simpleParser::Parser::expectEndModule() {
    auto parseStart = mCurrentToken;
    optional<tokenize::Token> possibleOperator = expectOperator(".");
    if (possibleOperator.has_value()) { // Operator found !
        optional<tokenize::Token> possibleIdentifier =
                expectIdentifier("end");
        if (possibleIdentifier.has_value()) {
            cout << "We reached the end of the module ! " << endl;
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

    while (mCurrentToken != mEndToken) {
        if (expectModelDefinition() || expectInputsDefinition() || expectOutputsDefinition() ||
            expectGateDefinition() || expectEndModule()) {

        } else {
            cerr << "Unknown identifier " << mCurrentToken->mText << endl;
            ++mCurrentToken;
        }
    }
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

simpleParser::Parser::Parser() {
    mTypes["model"] = Type("model", MODEL);
    mTypes["inputs"] = Type("inputs", INPUTS);
    mTypes["outputs"] = Type("outputs", OUTPUTS);
    mTypes["gate"] = Type("gate", GATE);
    mTypes["end"] = Type("end", END);
}

[[maybe_unused]] optional<simpleParser::Type> simpleParser::Parser::expectType() {
    optional<tokenize::Token> possibleType = expectIdentifier();
    if (!possibleType) {
        return nullopt;
    }

    auto foundType = mTypes.find(possibleType->mText);
    if (foundType == mTypes.end()) {
        --mCurrentToken;
        return nullopt;
    }

    return foundType->second;
}
