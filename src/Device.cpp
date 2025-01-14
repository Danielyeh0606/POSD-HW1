#include "Device.h"

void Device::addInputPin(Device* d){
    iPins.push_back(d);
}

int Device::getiPinSize(){
    return iPins.size();
}