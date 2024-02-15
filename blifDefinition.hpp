#pragma once


namespace simpleParser {
    using namespace std;

    class modelDefinition {
    public:
        string mName;
    };

    class ioDefinition {
    public:
        string mName;
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


    class netlistDefiniton {
    public:
        // Vector to hold input definitions
        modelDefinition modelName;
        vector<ioDefinition> inputs;
        vector<ioDefinition> outputs;
        vector<gateDefinition> gates;

    };
} // simpleParser
