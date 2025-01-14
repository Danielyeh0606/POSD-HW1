#include "Device.h"

void Device::addInputPin(Device* newDivice){
    iPins.push_back(newDivice);
}

int Device::getiPinSize(){
    return iPins.size();
}