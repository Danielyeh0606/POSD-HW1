#include "../src/LogicSimulator.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main(){
    LogicSimulator testSimulator;

    // generateAllInput testing
    for(int test_size = 1; test_size < 5; test_size++){
        printf("Size test %d:\n", test_size);
        for(vector<bool> item: testSimulator.generateAllInput(test_size)){
            for(bool value: item)
                printf("%d ", value);

            printf("\n");
        }
        printf("\n");
    }

    testSimulator.load("../File_1.lcf");

    // getSimulatorResult testing
    vector<bool> input{0, 1, 1};
    cout << "Test gate with input(0, 1, 1): ";
    for(bool out: testSimulator.getSimulationResult(input)) 
        cout << out << " " << endl;  
    cout << endl;
    

    // getTruthTable testing
    printf("Truth Table test %d:\n", testSimulator.getiPinSize());
    for(vector<bool> item: testSimulator.generateAllInput(testSimulator.getiPinSize())){
        // print input
        printf("Input: ");
        for(bool value: item)
            printf("%d ", value);

        // print output
        printf(", Output: ");
        for(bool value: testSimulator.getSimulationResult(item))
            printf("%d ", value);
        
        printf("\n");
    }
    printf("\n");

    
}