#ifndef DEVICE_H
#define DEVICE_H
#include <vector>
#include <string>
using namespace std;

class Device{
    protected:
        vector<Device*> iPins;
    public:
        virtual void addInputPin(Device*);
        virtual bool getOutput() = 0;
        virtual string getType() = 0;
        int getiPinSize();
};

#endif