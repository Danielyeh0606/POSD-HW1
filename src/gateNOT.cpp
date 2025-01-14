#include "gateNOT.h"

void gateNOT::addInputPin(Device* newDivice){
    if(iPins.size() == 0)
        iPins.push_back(newDivice);
    else
        printf("Error: NOT gate can't add more than one input pin\n");
}

bool gateNOT::getOutput(){
    return !(iPins[0]->getOutput());
}

string gateNOT::getType(){
    return "NOT";
}