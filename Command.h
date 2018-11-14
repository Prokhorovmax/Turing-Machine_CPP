
#ifndef TURINGMACHINE_COMMAND_H
#define TURINGMACHINE_COMMAND_H


class Command {

public:

    char newSymbol;
    char move;
    int newState;

    Command() = default;

    Command(char symbol, char move, int state) {
        this->newSymbol = symbol;
        this->newState = state;
        this->move = move;
    }
};


#endif //TURINGMACHINE_COMMAND_H
