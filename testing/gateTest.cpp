#include "../src/Device.h"
#include "../src/iPin.h"
#include "../src/oPin.h"
#include "../src/gateAND.h"
#include "../src/gateOR.h"
#include "../src/gateNOT.h"
#include "../src/LogicSimulator.h"

#include <stdio.h>
#include <iostream>
using namespace std;

int main(){
    LogicSimulator testCircuit;

    iPin* T_ipin = new iPin();
    T_ipin->setValue(true);
    iPin* F_ipin = new iPin();
    F_ipin->setValue(false);

    for(int type = 1; type <= 3; type++){
        Device* opin = new oPin();
        Device* gate = testCircuit.GateTable(type);
        
        gate->addInputPin(T_ipin);
        if(type != 3)// NOT gate only need one input
            gate->addInputPin(F_ipin);
        opin->addInputPin(gate);

        if(type != 3)
            printf("%s gate with input value 1, 0: %d\n", gate->getType().c_str(), opin->getOutput());
        else
            printf("%s gate with input value 1: %d\n", gate->getType().c_str(), opin->getOutput());
        
        delete gate;
        delete opin;
    }

    delete T_ipin;
    delete F_ipin;
}