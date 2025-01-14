#include "Device.h"
#ifndef GATEOR_H
#define GATEOR_H

class gateOR: public Device{
    public:
        bool getOutput() override;
        string getType() override;
};

#endif