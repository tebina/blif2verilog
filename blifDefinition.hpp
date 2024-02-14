#pragma once

#include "Type.hpp"


namespace simpleParser {
    using namespace std;

    class modelDefinition {
    public:
        string mName;
    };

    class inputDefinition {
    public:
        string mName;
    };

    class manyInputDefinition {
    public:
        vector<inputDefinition> mName;
    };

    class outputDefinition {
    public:
        string mName;
    };

    class manyOutputDefinition {
    public:
        vector<outputDefinition> mName;
    };

    class gateNetsDefinition {
    public:
        string mPin;
        string mName;
    };

    class gateDefinition {
    public:
        string mName;
        vector<gateNetsDefinition> mPins;
    };

} // simpleParser
