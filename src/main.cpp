#include <iostream>
#include "TextUI.h"
using namespace std;

bool isNumber(string line){
    for(char c: line){
        if(!isdigit(c))
            return false;
    }
    return true;
}

int main(){
    TextUI control;
    while(true){
        control.displayMenu();
    
        cout << "Command:";
        string command;
        cin >> command;
        if(isNumber(command)){
            control.processCommand(stoi(command));
        }else{
            cout << "The command must be positive integer.\n";
            cin.clear();
        }

        cout << endl;
    }
}