#include "Device.h"
#include <stdio.h>
#ifndef OPIN_H
#define OPIN_H

class oPin: public Device{
    public:
        ~oPin() override{};
        void addInputPin(Device*) override;
        bool getOutput() override;
        string getType() override;
};

#endif