#include "iPin.h"

void iPin::addInputPin(Device* newDivice){
    printf("Error: input pin can't add any input pin\n");
}

bool iPin::getOutput(){
    return value;
}

void iPin::setValue(bool b){
    value = b;
}

string iPin::getType(){
    return "Input Pin";
}