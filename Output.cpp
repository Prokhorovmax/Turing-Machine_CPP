
#include "Output.h"

void printTape(int headPos, string &tape, ofstream &output) {
    int length = tape.length();
    // Head line
    for (int i = 0; i < length; i++) {
        if (i == headPos) {
            cout << "V";
            output << "V";
        } else {
            cout << ".";
            output << ".";
        }
    }
    cout << "\n";
    output << "\n";

    // Tape
    cout << tape << "\n";
    output << tape << "\n";

    // Numbers
    int i = 0;
    int cond = 0;
    while (cond != length) {
        string str = to_string(i);
        cout << str;
        output << str;
        if (i < 9) {
            i++;
        } else {
            i = 0;
        }
        cond++;
    }
    cout << "\n\n";
    output << "\n\n";
}

void printCommand(int currentState, char currentSymbol, Command command, ofstream &output) {
    cout << "q" << currentState << ": " << currentSymbol << " " << command.move << " " << command.newSymbol
         << " q" << command.newState << "\n";
    output << "q" << currentState << ": " << currentSymbol << " " << command.move << " " << command.newSymbol
           << " q" << command.newState << "\n";
}

void printStart(ofstream &output) {
    cout << "START\n\n";
    output << "START\n\n";
}

void printEnd(ofstream &output) {
    cout << "END\n";
    output << "END\n";
}

void printStop(ofstream &output) {
    cout << "FORCED STOP\n";
    output << "FORCED STOP\n";
}