#ifndef TURINGMACHINE_PROCESS_H
#define TURINGMACHINE_PROCESS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Command.h"
#include "Output.h"

using namespace std;

class Process {

private:

    string alphabet;
    int headPos;
    string tape;
    vector<int> states;
    int statesNumber;
    vector<vector<Command>> commands;
    int flag;

public:

    Process(string &alphabet, int headPos, string &tape, vector<int> &states_, int statesNumber,
            vector<vector<Command>> &commands_, int flag) {
        this->alphabet = alphabet;
        this->headPos = headPos;
        this->tape = tape;
        this->statesNumber = statesNumber;
        this->flag = flag;

        states.reserve(static_cast<unsigned int>(statesNumber));
        for (int i = 0; i < statesNumber; ++i) {
            states[i] = states_[i];
        }

        commands.reserve(alphabet.length());
        for (int i = 0; i < alphabet.length(); ++i) {
            commands[i].reserve(static_cast<unsigned int>(statesNumber));
            for (int j = 0; j < statesNumber; ++j) {
                commands[i][j] = commands_[i][j];
            }
        }
    }

    int run(ofstream &outputFile);

};

#endif //TURINGMACHINE_PROCESS_H
