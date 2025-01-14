#include "../src/TextUI.h"
#include <stdio.h>
#include <iostream>
using namespace std;

int main(){
    TextUI textUI;
    
    printf("Test print menu:\n");
    textUI.displayMenu();

    printf("Test load file:\n");
    textUI.loadFile();

    printf("Test key in input value:\n");
    textUI.simulation();

    printf("Test print truth table:\n");
    textUI.displayTruthTable();

    printf("Test process command:\n");
    for(int command = 1; command < 5; command++){
        textUI.processCommand(command);
    }
}