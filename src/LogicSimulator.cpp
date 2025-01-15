#include "LogicSimulator.h"

LogicSimulator::~LogicSimulator(){
    clearDevice();
}

vector<bool> LogicSimulator::getSimulationResult(vector<bool> input){
    if(input.size() != iPins.size()){
        printf("Size of input value not equal with input pins!\n");
        return vector<bool>{};
    }
    
    // setting input pins
    for(int i = 0; i < iPins.size(); i++){
        iPins[i]->setValue(input[i]);
    }
    
    // getting output pins
    vector<bool> out;
    for(Device* d: oPins){
        out.push_back(d->getOutput());
    }
    return out;
}

vector<vector<bool>> LogicSimulator::getTruthTable(){
    if(iPins.size() == 0){
        printf("No circuits loaded yet!\n");
        return vector<vector<bool>>{};
    }

    vector<vector<bool>> allOut;
    
    for(vector<bool> input: generateAllInput(iPins.size()))
        allOut.push_back(getSimulationResult(input));
    
    return allOut;
}

void LogicSimulator::initDevice(int input_size, int gate_size){
    clearDevice();

    iPins.resize(input_size);
    circuit.resize(gate_size, nullptr);
    gate_is_connect.resize(gate_size);

    for(int i = 0; i < input_size; i++){
        iPins[i] = new iPin();
    }

    for(int i = 0; i < gate_size; i++){
        gate_is_connect[i] = false;
    }
}

void LogicSimulator::setGateType(int index, int type){
    circuit[index] = GateTable(type);
}

void LogicSimulator::setGate(int index, string text){
    istringstream readline(text);
    float information;

    readline >> information;//ignore type of gate

    //set input pin of gate
    while(information != 0){
        readline >> information;
        if(information < 0){
            circuit[index]->addInputPin(iPins[int(-information) - 1]);
        }else if(information > 0){
            circuit[index]->addInputPin(circuit[int(information) - 1]);
            gate_is_connect[information - 1] = true;
        }
    }
}

void LogicSimulator::load(string path){
    ifstream read(path);
    int input_size, gate_size;
    read >> input_size >> gate_size;
    initDevice(input_size, gate_size);
    
    string gate_info[gate_size];
    string line;
    getline(read, line);// ignore second line

    // initial type of all gate 
    for(int i = 0; i < circuit.size(); i++){
        getline(read, line);
        gate_info[i] = line;
        istringstream readline(line);
        int gateType;
        readline >> gateType;
        setGateType(i, gateType);
    }

    
    // set input pin of all gate
    for(int i = 0; i < circuit.size(); i++){
        setGate(i, gate_info[i]);
    }
    

    // confirm which gate should be connected with output pin
    for(int i = 0; i < gate_is_connect.size(); i++){
        if(!gate_is_connect[i]){
            oPins.push_back(new oPin());
            oPins[oPins.size() - 1]->addInputPin(circuit[i]);
        }
    } 
    
}

Device* LogicSimulator::GateTable(int index){
    switch (index)
    {
    case 1:
        return new gateAND();
        break;
    case 2:
        return new gateOR();
        break;
    case 3:
        return new gateNOT();
        break;
    default:
        printf("Error: wrong type of gate!\n");
        return nullptr;
        break;
    }
}

vector<vector<bool>> LogicSimulator::generateAllInput(int size){
    vector<vector<bool>> out;

    // initialize input value
    vector<bool> input;
    for(int i = 0; i < size; i++)
        input.push_back(0);

    bool end = false;
    while(!end){
        out.push_back(input);

        // check after input +1, next bit if get carry or not
        for(int i = input.size() - 1; i >= 0; i--){
            input[i] = !input[i];
            if(input[i])// 0 -> 1 => no carry
                break;
            else if(i == 0 && !input[i])// highest bit is 1 -> 0 => end
                end = true;
        }
    }

    return out;
}

void LogicSimulator::clearDevice(){
    for(Device* d: iPins)
        delete d;
    for(Device* d: circuit)
        delete d;
    for(Device* d: oPins)
        delete d;

    iPins.clear();
    circuit.clear();
    oPins.clear();
}

int LogicSimulator::getiPinSize(){
    return iPins.size();
}

int LogicSimulator::getoPinSize(){
    return oPins.size();
}

int LogicSimulator::getGateSize(){
    return circuit.size();
}

void LogicSimulator::printGateType(int index){
    if(circuit[index] == nullptr)
        printf("gate isn't set\n");
    else{
        printf("Gate %d: %s\n", index + 1, circuit[index]->getType().c_str());
    }
}

void LogicSimulator::printGateiPinSize(int index){
    if(circuit[index] == nullptr)
        printf("gate isn't set\n");
    else{
        printf("Gate %d: %d\n", index + 1, circuit[index]->getiPinSize());
    }
}