
#ifndef TURINGMACHINE_OUTPUT_H
#define TURINGMACHINE_OUTPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include "Command.h"

using namespace std;

void printTape(int headPos, string &tape, ofstream &output);

void printCommand(int currentState, char currentSymbol, Command command, ofstream &output);

void printStart(ofstream &output);

void printEnd(ofstream &output);

void printStop(ofstream &output);

#endif //TURINGMACHINE_OUTPUT_H
