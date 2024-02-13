#include "parser.hpp"
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
                cout << "We have a model name: " << possibleModelName->mText << endl;
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
    if (possibleOperator.has_value()) { // Operator found !
        optional<tokenize::Token> possibleIdentifier =
                expectIdentifier("inputs");
        if (possibleIdentifier.has_value()) {
            optional<tokenize::Token> possibleModelName = expectIdentifier();
            if (possibleModelName.has_value()) {
                cout << "We have inputs name: " << possibleModelName->mText << endl;
                return true;
        } else {
            mCurrentToken = parseStart;
        }
    } else {
        mCurrentToken = parseStart;
    }}
    return false;
}

bool simpleParser::Parser::expectOutputsDefinition() {
    auto parseStart = mCurrentToken;
    optional<tokenize::Token> possibleOperator = expectOperator(".");
    if (possibleOperator.has_value()) { // Operator found !
        optional<tokenize::Token> possibleIdentifier =
                expectIdentifier("outputs");
        if (possibleIdentifier.has_value()) {
            optional<tokenize::Token> possibleModelName = expectIdentifier();
            if (possibleModelName.has_value()) {
                cout << "We have outputs name: " << possibleModelName->mText << endl;
                return true;
            } else {
                mCurrentToken = parseStart;
            }
        } else {
            mCurrentToken = parseStart;
        }}
    return false;
}

bool simpleParser::Parser::expectGateDefinition() {
    auto parseStart = mCurrentToken;
    optional<tokenize::Token> possibleOperator = expectOperator(".");
    if (possibleOperator.has_value()) { // Operator found !
        optional<tokenize::Token> possibleIdentifier =
                expectIdentifier("gate");
        if (possibleIdentifier.has_value()) {
            optional<tokenize::Token> possibleModelName = expectIdentifier();
            if (possibleModelName.has_value()) {
                cout << "We have a gate name: " << possibleModelName->mText << endl;
                return true;
            } else {
                mCurrentToken = parseStart;
            }
        } else {
            mCurrentToken = parseStart;
        }}
    return false;
}

void simpleParser::Parser::parse(vector<tokenize::Token> &tokens) {
    mEndToken = tokens.end();
    mCurrentToken = tokens.begin();

    while (mCurrentToken != mEndToken) {
        if (expectModelDefinition()) {

        } else {
            cerr << "Unknown identifier " << mCurrentToken->mText << endl;
            ++mCurrentToken;
        }

        if (expectInputsDefinition()) {

        } else {
            cerr << "Unknown identifier " << mCurrentToken->mText << endl;
            ++mCurrentToken;
        }

        if (expectOutputsDefinition()) {
        } else {
            cerr << "Unknown identifier " << mCurrentToken->mText << endl;
            ++mCurrentToken;
        }

        if (expectGateDefinition()) {
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
