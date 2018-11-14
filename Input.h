#include <fstream>
#include <iostream>
#include <string.h>

#ifndef TURINGMACHINE_INPUT_H
#define TURINGMACHINE_INPUT_H

using namespace std;

class Input {

private:
    ifstream inputTapeFile;
    ifstream alphabetFile;
    ifstream machineFile;
    ofstream outputFile;
    int flag;

    void readFiles(int argc, char *argv[]);

    void fileOpening(ifstream &fileName, string arg, string nextArg, string flag);

    void information();

public:
    Input(int argc, char *argv[]) {
        readFiles(argc, argv);
    }

    ifstream &getInputTapeFile();

    ifstream &getAlphabetFile();

    ifstream &getMachineFile();

    ofstream &getOutputFile();

    int &getFlag();
};


#endif //TURINGMACHINE_INPUT_H
