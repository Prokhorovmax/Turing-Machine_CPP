#ifndef TURINGMACHINE_PARSER_H
#define TURINGMACHINE_PARSER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Command.h"
#include "Utility.h"

using namespace std;

class Parser {

public:

    void parseAlphabet(ifstream &alphabetFile);

    void parseTape(ifstream &inputTapeFile);

    void parseMachine(ifstream &machineFile);

    string &getAlphabet();

    string &getTape();

    int &getHeadPos();

    int &getNumberOfStates();

    vector<int> &getStateNumbers();

    vector<vector<Command>> &getCommands();


private:


    string alphabet;
    string tape;
    int headPos;
    int numberOfStates;
    vector<int> stateNumbers;
    vector<vector<Command>> commands;

    Command parseCommand(string str, int index, int line);

    int parseState(string str, int index);

    void setCommands(vector<vector<Command>> &commands_temp, int n, int m);

};


#endif //TURINGMACHINE_PARSER_H
