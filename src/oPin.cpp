#include "oPin.h"

void oPin::addInputPin(Device* newDivice){
    if(iPins.size() == 0)
        iPins.push_back(newDivice);
    else
        printf("Error: output pin can't add more than one input pin\n");
}

bool oPin::getOutput(){
    if(iPins.size() == 0)
        printf("output pin isn't connected any gate.\n");
    else{
        return iPins[0]->getOutput();
    }
    
    return false;
}

string oPin::getType(){
    return "Output Pin";
}