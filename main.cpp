#include "main.h"

using namespace std;

int main(int argc, char *argv[]) {
    Input input(argc, argv);

    Parser parser;
    parser.parseAlphabet(input.getAlphabetFile());
    parser.parseTape(input.getInputTapeFile());
    parser.parseMachine(input.getMachineFile());

    Process process(parser.getAlphabet(), parser.getHeadPos(), parser.getTape(), parser.getStateNumbers(),
                    parser.getNumberOfStates(), parser.getCommands(), input.getFlag());
    process.run(input.getOutputFile());


    // Fast check/debug/run without console input. Comment everything above and use code below.

//    Parser parser;
//
//    ifstream alphabetFIle ("alphabet.txt");
//    ifstream inputTapeFIle ("inputtape.txt");
//    ifstream machineFIle ("machine.txt");
//    ofstream outputFIle ("output.txt");
//
//    parser.parseAlphabet(alphabetFIle);
//    parser.parseTape(inputTapeFIle);
//    parser.parseMachine(machineFIle);
//
//    Process process(parser.getAlphabet(), parser.getHeadPos(), parser.getTape(), parser.getStateNumbers(), parser.getNumberOfStates(),
//                    parser.getCommands(), 0); // 0 - simple run; 1 - debug mode.
//    process.run(outputFIle);
}