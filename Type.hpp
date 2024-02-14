#pragma once

#include <string>
#include <vector>


namespace simpleParser {


    enum BUILTIN_KEYWORDS {
        MODEL, INPUTS, OUTPUTS, GATE, END
    };

    class Type {
    public:
        explicit Type(std::string name = "", enum BUILTIN_KEYWORDS type = MODEL)
                : mName(std::move(name)), mType(type) {};
        std::string mName;
        enum BUILTIN_KEYWORDS mType;
        std::vector<Type> mField;
    };
} // simpleParser
