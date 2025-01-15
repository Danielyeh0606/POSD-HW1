#include "TextUI.h"

void TextUI::displayMenu(){
    cout << "1. Load logic circuit file\n";
    cout << "2. Simulation\n";
    cout << "3. Display truth table\n";
    cout << "4. Exit\n";
}

void TextUI::processCommand(int command){
    switch (command)
    {
    case 1:
        loadFile();
        break;
    case 2:
        simulation();
        break;
    case 3:
        displayTruthTable();
        break;
    case 4:
        Exit();
        break;
    default:
        cout << "The command must between 1 and 4.\n";
        break;
    }
}

bool TextUI::isLegalNumber(string line){
    istringstream readline(line);
    string word;

    while(readline >> word){// negative integer or positive number
        int start = (word[0] == '-')? 1:0;
        bool dot_can_be_exist = (word[0] == '-')? 0:1;
        
        for(int i = start; i < word.size(); i++){
            if(word[i] == '.' && dot_can_be_exist){
                dot_can_be_exist = false;// can't appear more than one dot
                continue;
            }

            if(!isdigit(word[i]))
                return false;
        }
    }

    return true;
}

int TextUI::wordCount(string line){
    istringstream readline(line);
    string word;
    int count = 0;
    while(readline >> word)
        count++;
    
    return count;
}

bool TextUI::legalInputPin(string line, int ipin_size, int gate_size){
    istringstream readline(line);
    float ipin;
    readline >> ipin;// ignore type of gate

    while(readline >> ipin){
        if(ipin < 0 && int(-ipin) > ipin_size)
            return false;
        else if(ipin > 0 && int(ipin) > gate_size)
            return false;
    }
    
    return  true;
}

bool TextUI::checkFileFormat(string path){
    bool result = true;

    ifstream readFile(path);
    if(!readFile.is_open()){// check exist
        result = false;
    }else{// check format
        string line;
        int num_of_line = 3;
        
        int ipin_size = 0, gate_size = 0;
        for(int i = 0; i < gate_size + 2; i++){
            getline(readFile, line);
            if(i == 0){// first line
                if(wordCount(line) > 1 || !isLegalNumber(line)){
                    printf("Error in line 1\n");
                    result = false;
                }else
                    ipin_size = stoi(line);
                
            }else if(i == 1){// second line
                if(wordCount(line) > 1 || !isLegalNumber(line)){
                    printf("Error in line 2\n");
                    result = false;
                }else
                    gate_size = stoi(line);
            }else{// set input pin of gate
                if(!isLegalNumber(line) || !legalInputPin(line, ipin_size, gate_size)){
                    printf("Error in line %d\n", i + 1);
                    result = false;
                }
            }
        }
    }

    return result;
}

void TextUI::loadFile(){
    cout << "Please key in a file path: ";
    string path;
    cin >> path;

    if(checkFileFormat(path)){
        Circuit.load(path);
        printf("Circuit: %d input pins, %d output pins and %d gates\n", 
            Circuit.getiPinSize(), Circuit.getoPinSize(), Circuit.getGateSize());
    }else{
        cout << "File not found or file format error!!\n";
    }
}

void TextUI::simulation(){
    // check the file has been loaded already
    if(Circuit.getiPinSize() == 0){
        cout << "Please load an lcf file, before using this operation.\n";
        return ;
    }

    vector<bool> input;
    for(int i = 0; i < Circuit.getiPinSize(); i++){
        printf("Please key in the value of input pin %d:", i + 1);
        char in;
        cin >> in;

        // check error input value
        while(in != '1' && in != '0'){
            printf("The value of input pin must be 0/1\n");
            printf("Please key in the value of input pin %d:", i + 1);
            cin >> in;
        }

        input.push_back(in == '1');
    }

    vector<bool> result = Circuit.getSimulationResult(input);
    
    printf("Simulation Result:\n");
    displayResultTitle();

    // print result
    for(bool in: input) printf("%-2d", in);
    printf("|");
    for(bool out: result) printf("%2d", out);
    printf("\n");
}

void TextUI::displayTruthTable(){
    // check the file has been loaded already
    if(Circuit.getiPinSize() == 0){
        cout << "Please load an lcf file, before using this operation.\n";
        return ;
    }

    vector<vector<bool>> input = Circuit.generateAllInput(Circuit.getiPinSize());
    vector<vector<bool>> output = Circuit.getTruthTable();

    printf("Truth table:\n");
    displayResultTitle();
    
    // print all result
    for(int item = 0; item < input.size(); item++){
        for(bool in: input[item]) 
            printf("%-2d", in);
        printf("|");
        for(bool out: output[item])
            printf("%2d", out);
        printf("\n");
    }
}

void TextUI::Exit(){
    printf("Goodbye, thanks for using LS.");
    Circuit.clearDevice();
    exit(0);
}

void TextUI::displayResultTitle(){
    for(int i = 0; i < Circuit.getiPinSize(); i++) printf("i ");
    printf("|");
    for(int i = 0; i < Circuit.getoPinSize(); i++) printf(" o");
    printf("\n");
    for(int i = 0; i < Circuit.getiPinSize(); i++) printf("%-2d", i + 1);
    printf("|");
    for(int i = 0; i < Circuit.getoPinSize(); i++) printf("%2d", i + 1);
    printf("\n");
    for(int i = 0; i < Circuit.getiPinSize(); i++) printf("--");
    printf("+");
    for(int i = 0; i < Circuit.getoPinSize(); i++) printf("--");
    printf("\n");
}