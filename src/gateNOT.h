#include "Device.h"
#include <stdio.h>
#ifndef GATENOT_H
#define GATENOT_H

class gateNOT: public Device{
    public:
        ~gateNOT() override{};
        void addInputPin(Device*) override;
        bool getOutput() override;
        string getType() override;
};

#endif