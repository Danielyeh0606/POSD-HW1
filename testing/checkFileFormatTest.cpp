#include "../src/TextUI.h"
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

int main(){
    TextUI textUI;
    string file_1 = "errorFile_1.lcf";
    string file_2 = "errorFile_2.lcf";
    string file_3 = "errorFile_3.lcf";
    string file_4 = "rightFile.lcf";

    printf("Test errorFile_1.lcf:\n");
    textUI.checkFileFormat(file_1);
    printf("\n");

    printf("Test errorFile_2.lcf:\n");
    textUI.checkFileFormat(file_2);
    printf("\n");

    printf("Test errorFile_3.lcf:\n");
    textUI.checkFileFormat(file_3);
    printf("\n");

    printf("Test rightFile.lcf:\n");
    textUI.checkFileFormat(file_4);
    printf("\n");
}