
#include "Input.h"

void Input::readFiles(int argc, char *argv[]) {
    if (argc == 1) {
        information();
        cout << "\nProcess finished with exit code 0\n";
        exit(0);
    }

    if ((argc != 9) && (argc != 10)) {
        cout << "Wrong number of arguments in command line launch\n";
        cout << "\nProcess finished with exit code 22\n";
        exit(22);
    }

    for (int i = 1; i < 8; i++) {
        fileOpening(alphabetFile, argv[i], argv[i + 1], "-a");
        fileOpening(inputTapeFile, argv[i], argv[i + 1], "-i");
        fileOpening(machineFile, argv[i], argv[i + 1], "-q");
        if (argv[i] == "-o") {
            outputFile.open(argv[i + 1]);
            if (!outputFile) {
                cout << "Cannot get file " << argv[i + 1] << "\n";
                cout << "\nProcess finished with exit code 23\n";
                exit(23);
            }
        }
    }
    if ((!alphabetFile) || (!inputTapeFile) || (!machineFile) || (!outputFile)) {
        cout << "Wrong format of command line launch\n";
        cout << "\nProcess finished with exit code 24\n";
        exit(24);
    }

    if ((argc == 10) && (strcmp(argv[9], "-debug") == 0)) {
        flag = 1;
    } else {
        flag = 0;
    }
}

void Input::fileOpening(ifstream &fileName, string arg, string nextArg, string flag) {
    if (arg == flag) {
        fileName.open(nextArg);
        if (!fileName) {
            cout << "Cannot get file " << nextArg << endl;
            cout << "\nProcess finished with exit code 23\n";
            exit(23);
        }
    }
}

void Input::information() {
    cout << ("Turing Machine simulator.\n"
            "The simulator is based on a text representation.\n"
            "It converts the input tape according to the commands of state-control machine.\n"
            "A feature of this machine is its one-sidedness.\n"
            "It means that head-pointer cannot go to the left of the initial position.\n\n"
            "To RUN the program type this line:\n"
            "TuringMachine__.exe -a alphabet.txt -i inputtape.txt -q machine.txt -o output.txt [-debug]\n"
            "Format of alphabet input file:\n"
            "0123ABC\n"
            "Format of input tape file:\n"
            "....V....\n"
            "____1010_\n"
            "Format of state-machine input file:\n"
            ". .q1. .q2.\n"
            "0 1>q1 1>q1\n"
            "1 2>q1 2>q1\n"
            "2 0>q2 0.q0\n"
            "_ _.q0 _.q0\n"
            "\n"
            "Symbol '_' stands for empty cell.\n"
            "Flags '-a', '-i', '-q', '-o' must be placed in front of the corresponding file.\n"
            "Flag '-debug' runs debug configuration, where:\n"
            "'N' -> next step\n"
            "'RUN' -> running to the end\n"
            "'STOP' -> stops the program\n");
}

ifstream &Input::getInputTapeFile() {
    return inputTapeFile;
}

ifstream &Input::getAlphabetFile() {
    return alphabetFile;
}

ifstream &Input::getMachineFile() {
    return machineFile;
}

ofstream &Input::getOutputFile() {
    return outputFile;
}

int &Input::getFlag() {
    return flag;
}
