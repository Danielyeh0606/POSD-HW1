#include "gateAND.h"

bool gateAND::getOutput(){
    bool out = true;

    for(Device* d: iPins){
        out = (out && d->getOutput());
    }
    
    return out;
}

string gateAND::getType(){
    return "AND";
}