
#include "Process.h"

int Process::run(ofstream &outputFile) {
    printStart(outputFile);
    printTape(headPos, tape, outputFile);
    int step = 0;
    int currentState = 1;
    while (step != 1000) {
        step++;
        char ch = tape[headPos];
        int i = alphabet.find_first_of(ch) - alphabet.find_first_of(alphabet[0]);
        int j = 0;
        for (int k = 0; k < statesNumber; k++) {
            if (currentState == states[k]) {
                j = k;
                break;
            }
        }
        if ((commands[i][j].newSymbol == '?') && (commands[i][j].move == '?') && (commands[i][j].newState) == -1) {
            cout << "The command for such combination of state and symbol was not found\n";
            cout << "\nProcess finished with exit code 20\n";
            outputFile.close();
            exit(20);
        }
        printCommand(currentState, tape[headPos], commands[i][j], outputFile);
        currentState = commands[i][j].newState;
        tape[headPos] = commands[i][j].newSymbol;
        if (commands[i][j].move == '>') {
            headPos++;
        }
        if (commands[i][j].move == '<') {
            headPos--;
        }
        printTape(headPos, tape, outputFile);
        if (currentState == 0) {
            printEnd(outputFile);
            outputFile.close();
            states.clear();
            for (int l = 0; l < alphabet.length(); l++) {
                commands[l].clear();
            }
            commands.clear();
            cout << "\nProcess finished with exit code 0\n";
            exit(0);
        }
        if (headPos < 0) {
            cout << "The head went beyond the left border\n";
            cout << "\nProcess finished with exit code 21\n";
            exit(21);
        }

        if (flag == 1) {
            string action;
            while (true) {
                cin >> action;
                cin.get();
                fflush(stdin);
                if ((action == "n") || (action == "N")) {
                    break;
                }
                if ((action == "run") || (action == "RUN")) {
                    flag = 0;
                    break;
                }
                if ((action == "stop") || (action == "STOP")) {
                    printStop(outputFile);
                    outputFile.close();
                    states.clear();
                    for (int l = 0; l < alphabet.length(); l++) {
                        commands[l].clear();
                    }
                    commands.clear();
                    cout << "\nProcess finished with exit code 1\n";
                    exit(1);
                } else {
                    cout << "Unknown action. Try this: 'N'; 'RUN'; 'STOP';\n";
                }
            }
        }
    }
    printStop(outputFile);
    cout << "RUNTIME ERROR\n";
    outputFile.close();
    states.clear();
    for (int l = 0; l < alphabet.length(); l++) {
        commands[l].clear();
    }
    commands.clear();
    cout << "\nProcess finished with exit code 25\n";
    exit(25);
}
