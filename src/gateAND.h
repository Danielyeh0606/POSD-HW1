#include "Device.h"
#ifndef GATEAND_H
#define GATEAND_H

class gateAND: public Device{
    public:
        ~gateAND() override{};
        bool getOutput() override;
        string getType() override;
};

#endif