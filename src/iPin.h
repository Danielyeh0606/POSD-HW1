#include "Device.h"
#include <stdio.h>
#ifndef IPIN_H
#define IPIN_H

class iPin: public Device{
    private:
        bool value;

    public:
        ~iPin() override{};
        void setValue(bool);
        void addInputPin(Device*) override;
        bool getOutput() override;
        string getType() override;
};

#endif