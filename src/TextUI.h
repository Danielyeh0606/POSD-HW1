#ifndef TEXTUI_H
#define TEXTUI_H
#include "LogicSimulator.h"
#include <iostream> 
#include <sstream>
#include <string>
using namespace std;


class TextUI{
    private:
        LogicSimulator Circuit;
    public:
        void displayMenu();
        void processCommand(int);

        bool isLegalNumber(string);
        int wordCount(string);
        bool legalInputPin(string line, int ipin_size, int gate_size);
        bool checkFileFormat(string);

        void loadFile();
        void simulation();
        void displayTruthTable();
        void Exit();

        void displayResultTitle();
};

#endif
