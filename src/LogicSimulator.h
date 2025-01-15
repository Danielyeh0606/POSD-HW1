#ifndef LOGICSIMULATOR_H
#define LOGICSIMULATOR_H
#include "Device.h"
#include "iPin.h"
#include "oPin.h"
#include "gateAND.h"
#include "gateOR.h"
#include "gateNOT.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class LogicSimulator{
    private:
        vector<Device*> circuit;
        vector<iPin*> iPins;
        vector<Device*> oPins;
        vector<bool> gate_is_connect;

    public:
        ~LogicSimulator();

        // for simulation
        vector<bool> getSimulationResult(vector<bool> input);
        vector<vector<bool>> generateAllInput(int size);
        vector<vector<bool>> getTruthTable();

        // for load file
        Device* GateTable(int index);
        void initDevice(int input_size, int gate_size);
        void setGateType(int index, int type);
        void setGate(int index, string text);
        void load(string path);

        void clearDevice();

        // for test
        int getiPinSize();
        int getoPinSize();
        int getGateSize();

        void printGateType(int index);
        void printGateiPinSize(int index);
};

#endif