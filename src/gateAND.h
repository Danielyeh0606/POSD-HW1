#include "Device.h"
#ifndef GATEAND_H
#define GATEAND_H

class gateAND: public Device{
    public:
        bool getOutput() override;
        string getType() override;
};

#endif