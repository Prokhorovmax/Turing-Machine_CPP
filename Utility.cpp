
#include "Utility.h"

using namespace std;


int isNumber(char ch) {
    string num = "0123456789";
    if (num.find(ch) != std::string::npos) {
        return ch - '0';
    } else {
        return -1;
    }
}

int pow(int x, int y) {
    int res = 1;
    for (int i = 0; i < y; i++) {
        res = res * x;
    }
    return res;
}