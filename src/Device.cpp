#include "Device.h"

Device::~Device(){
    iPins.clear();
}

void Device::addInputPin(Device* newDivice){
    iPins.push_back(newDivice);
}

int Device::getiPinSize(){
    return iPins.size();
}