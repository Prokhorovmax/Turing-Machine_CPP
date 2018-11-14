
#include "Parser.h"

using namespace std;

// Alphabet
void Parser::parseAlphabet(ifstream &alphabetFile) {
    string alphabetString;
    getline(alphabetFile, alphabetString); // Stores alphabet characters
    int alphabetLength = alphabetString.length();
    for (int i = 0; i < alphabetLength; i++) {
        if (alphabetString.find_first_of(alphabetString[i]) != alphabetString.find_last_of(alphabetString[i])) {
            cout << "Symbols in alphabet input file cannot have duplicate\n";
            cout << "\nProcess finished with exit code 15\n";
            exit(15);
        }
    }
    if (alphabetString.find('_') == std::string::npos) {
        alphabetString.append("_");
    }
    alphabet = alphabetString;
}


// Tape
void Parser::parseTape(ifstream &inputTapeFile) {
    // Head
    string headString;
    getline(inputTapeFile, headString);
    headPos = -1; // Stores position of the head, counts from 0
    for (int i = 0; i < headString.length(); i++) {
        if ((headString[i] != '.') && (headString[i] != 'V')) {
            cout << "The problem of determining the position of the head\n";
            cout << "Input tape file. Error in line: 1\n";
            cout << "\nProcess finished with exit code 17\n";
            exit(17);
        } else if ((headString[i] == 'V') && (headPos > 0)) {
            cout << "Tape must contain exactly one head\n";
            cout << "Input tape file. Error in line: 1\n";
            cout << "\nProcess finished with exit code 18\n", 18;
            exit(18);
        } else if (headString[i] == 'V') {
            headPos = i;
        }
    }
    if (headPos < 0) {
        cout << "Tape must contain exactly one head\n";
        cout << "Input tape file. Error in line: 1\n";
        cout << "\nProcess finished with exit code 18\n";
        exit(18);
    }

    // Initial tape
    getline(inputTapeFile, tape);
    for (char ch : tape) {
        if (alphabet.find(ch) == std::string::npos) {
            cout << "Tape must contain only alphabet characters\n";
            cout << "Input tape file. Error in line: 2\n";
            cout << "\nProcess finished with exit code 16\n";
            exit(16);
        }
    }
}

// State-machine
void Parser::parseMachine(ifstream &machineFile) {
    numberOfStates = 0;
    int alphabetLength = alphabet.length();
    stateNumbers.reserve(10);
    vector<int> stateIndexes; // Start line index of each state column
    stateIndexes.reserve(10);


    // Parsing first line of state-machine input data file
    string firstMachineLine;
    getline(machineFile, firstMachineLine);
    if ((firstMachineLine[0] != '.') && (firstMachineLine[1] != ' ')) {
        cout << "Wrong state-machine input data format\n";
        cout << "State-machine input file. Error in line: 1\n";
        cout << "\nProcess finished with exit code 5\n";
        exit(5);
    }
    for (int i = 2; i < firstMachineLine.length() - 1; i++) {
        if (((isNumber(firstMachineLine[i]) == -1) && (firstMachineLine[i] != 'q') && (firstMachineLine[i] != '.') &&
             (firstMachineLine[i] != ' ')) ||
            ((firstMachineLine[i] == '.') && (firstMachineLine[i + 1] != ' ') && (firstMachineLine[i + 1] != 'q') &&
             (firstMachineLine[i + 1] != '\0')) ||
            ((firstMachineLine[i] == 'q') && (isNumber(firstMachineLine[i + 1]) == -1)) ||
            ((isNumber(firstMachineLine[i]) != -1) && (isNumber(firstMachineLine[i + 1]) == -1) &&
             (firstMachineLine[i + 1] != '.')) ||
            ((firstMachineLine[i] == ' ') && (firstMachineLine[i + 1] != ' ') && (firstMachineLine[i + 1] != '.') &&
             (firstMachineLine[i + 1] != '\0'))) {
            cout << "Wrong state-machine input data format\n";
            cout << "State-machine input file. Error in line: 1\n";
            cout << "\nProcess finished with exit code 5\n";
            exit(5);
        } else if ((firstMachineLine[i] == '.') && (firstMachineLine[i + 1] == 'q')) {
            stateNumbers[numberOfStates] = parseState(firstMachineLine, i + 2);
            stateIndexes[numberOfStates] = i;
            numberOfStates++;
        }
    }

    vector<vector<Command>> commands_temp(static_cast<unsigned int>(alphabetLength),
                                          vector<Command>(static_cast<unsigned int>(numberOfStates)));

    // Parsing state-machine commands
    for (int i = 0; i < alphabetLength; i++) {
        string line;
        getline(machineFile, line);
        if (line[0] == '\0') {
            cout << "State-machine must contain all alphabet symbols in the first column\n";
            cout << "State-machine input file. Error in line: " << i + 2 << "\n";
            cout << "\nProcess finished with exit code 7\n";
            exit(7);
        }
        if ((i == alphabetLength - 1) && (line[line.length() - 1]) == '\n') {
            cout << "State-machine input file cannot have additional line at the end\n";
            cout << "State-machine input file. Error in line: " << i + 2 << "\n";
            cout << "\nProcess finished with exit code 12\n";
            exit(12);
        }
        if (line[0] != alphabet[i]) {
            if (line.length() == 0) {
                cout << "Empty line in state-machine file if forbidden\n";
            }
            cout << "First symbols of lines in state-machine file must have the same sequence "
                    "as the sequence of characters in the alphabet\n";
            cout << "State-machine input file. Error in line: " << i + 2 << "\n";
            cout << "\nProcess finished with exit code 14\n", 14;
            exit(14);
        }

        int prev = 1;
        for (int j = 0; j < numberOfStates; j++) {
            int n = stateIndexes[j];
            if ((line[n] == NULL) || (line[n] == '\0')) {
                Command command('?', '?', -1);
                commands_temp[i][j] = command;
                continue;
            }
            for (int k = prev + 1; k < n; k++) {
                if (line[k] != ' ') {
                    cout << "The state columns in the input file must have strong structure separated by spaces\n";
                    cout << "State-machine input file. Error in line: " << i + 2 << "\n";
                    cout << "\nProcess finished with exit code 10\n";
                    exit(10);
                }
            }
            commands_temp[i][j] = parseCommand(line, n, i + 2);
            if ((commands_temp[i][j].newSymbol == '?') && (commands_temp[i][j].move == '?') &&
                (commands_temp[i][j].newState == -1)) {
                continue;
            }
            if (alphabet.find(commands_temp[i][j].newSymbol) == std::string::npos) {
                cout << "New tape symbol must be from alphabet\n";
                cout << "State-machine input file. Error in line: " << i + 2 << "\n";
                cout << "\nProcess finished with exit code 8\n";
                exit(8);
            }
            if ((commands_temp[i][j].move != '.') && (commands_temp[i][j].move != '>') &&
                (commands_temp[i][j].move != '<')) {
                cout << "Unknown move command\n";
                cout << "State-machine input file. Error in line: " << i + 2 << "\n";
                cout << "\nProcess finished with exit code 9\n";
                exit(9);
            }
            int exist = 0;
            for (int k = 0; k < numberOfStates; k++) {
                if (stateNumbers[k] == commands_temp[i][j].newState) {
                    exist = 1;
                    break;
                }
            }
            if ((commands_temp[i][j].newState != 0) && (exist == 0)) {
                cout
                        << "New state in commands must be present in the first line of state-machine table (it must exist)\n";
                cout << "State-machine input file. Error in line: " << i + 2 << "\n";
                cout << "\nProcess finished with exit code 13\n";
                exit(13);
            }
            string stateNumStr;
            stateNumStr = to_string(commands_temp[i][j].newState);
            prev = n + 2 + stateNumStr.length();
        }
    }
    setCommands(commands_temp, alphabetLength, numberOfStates);
    stateIndexes.clear();
}


// Determination of state number
int Parser::parseState(string str, int index) {
    int stateNumber = 0;
    int i = index;
    int rank = 0;
    while (isNumber(str[i]) != -1) {
        rank++;
        i++;
    }
    i = index;
    while (rank > 0) {
        stateNumber += (str[i] - '0') * pow(10, rank - 1);
        rank--;
        i++;
    }
    if (stateNumber > 0) {
        return stateNumber;
    } else {
        cout << "Wrong state number\n";
        cout << "Error in line: 1\n";
        cout << "\nProcess finished with exit code 6\n";
        exit(6);
    }
}

// Making command from string
Command Parser::parseCommand(string str, int index, int line) {
    Command command{};
    if ((str[index] == ' ') && (str[index + 1] == ' ') && (str[index + 2] == ' ') && (str[index + 3] == ' ')) {
        command.newSymbol = '?';
        command.move = '?';
        command.newState = -1;
        return command;
    }
    command.newSymbol = str[index];
    command.move = str[index + 1];
    if (str[index + 2] != 'q') {
        cout << "Wrong state-machine command format\n";
        cout << "State-machine input file. Error in line: " << line << "\n";
        cout << "\nProcess finished with exit code 11\n";
        exit(11);
    }
    int i = index + 3;
    int rank = 0;
    int num = 0;
    if (isNumber(str[i]) == -1) {
        cout << "Wrong state-machine command format\n";
        cout << "State-machine input file. Error in line: " << line << "\n";
        cout << "\nProcess finished with exit code 11\n";
        exit(11);
    }
    while ((str[i] != ' ') && (str[i] != '\0')) {
        if (isNumber(str[i]) != -1) {
            rank++;
            i++;
        } else {
            cout << "Wrong state number\n";
            cout << "State-machine input file. Error in line: " << line << "\n";
            cout << "\nProcess finished with exit code 6\n";
            exit(6);
        }
    }
    i = index + 3;
    while (rank > 0) {
        num += (str[i] - '0') * pow(10, rank - 1);
        rank--;
        i++;
    }
    command.newState = num;
    return command;
}

string &Parser::getAlphabet() {
    return alphabet;
}

string &Parser::getTape() {
    return tape;
}

int &Parser::getHeadPos() {
    return headPos;
}

int &Parser::getNumberOfStates() {
    return numberOfStates;
}

vector<int> &Parser::getStateNumbers() {
    return stateNumbers;
}

vector<vector<Command>> &Parser::getCommands() {
    return commands;
}

void Parser::setCommands(vector<vector<Command>> &commands_temp, int n, int m) {
    commands.reserve(static_cast<unsigned int>(n));
    for (int i = 0; i < n; ++i) {
        commands[i].reserve(static_cast<unsigned int>(m));
        for (int j = 0; j < m; ++j) {
            commands[i][j] = commands_temp[i][j];
        }
    }
}
