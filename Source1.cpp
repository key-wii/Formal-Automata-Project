#include <iostream>
#include <iomanip>
#include <string>
#include<stdio.h>
#include<ctype.h>
#include <vector>
#include "input.h"
using namespace std;

void inputNum() {
    string input;
    vector<int> whole;
    vector<int> dec;
    vector<int> exp;
    long double full = 0;
    do {
        whole.clear();
        dec.clear();
        exp.clear();

        cout << "Please input a floating point number (or q to quit)\n";
        cout << "> ";
        cin >> input;

        int i = 1;
        char prevSymbol;
        char nextSymbol = input[0];
        int wholeDigits = 1;

        bool decimal = nextSymbol == '.';
        if (decimal) {
            i++;
            wholeDigits = 0;
        }
        int decPlace = 0;

        bool exponent = false;
        bool expFirst = true;
        int expSign = 1;

        bool suffix = false;
        bool fail = false;

        if (nextSymbol == 'q' || nextSymbol == 'Q') return;
        else if (decimal || isdigit(nextSymbol)) {
            if (!decimal) whole.push_back((int)nextSymbol - 48); //0 in ASCII is 48
            while (i < input.length() && !decimal) {
                prevSymbol = nextSymbol;
                nextSymbol = input[i];
                if (isdigit(nextSymbol)) {
                    wholeDigits++;
                    whole.push_back((int)nextSymbol - 48); //0 in ASCII is 48
                }
                else if (nextSymbol == '_') {
                    if (i == input.length() - 1) {
                        fail = true;
                        break;
                    }
                }
                else if (i == input.length() - 1 && (nextSymbol == 'f' || nextSymbol == 'F' || nextSymbol == 'd' || nextSymbol == 'D')) {
                    suffix = true;
                }
                else if (i != input.length() - 1 && (nextSymbol == 'e' || nextSymbol == 'E')) {
                    exponent = true;
                    i++;
                    break;
                }
                else if (nextSymbol == '.') {
                    if (prevSymbol == '_') {
                        fail = true;
                        break;
                    }
                    else decimal = true;
                }
                else {
                    fail = true;
                    break;
                }
                i++;
            }
            if (decimal && !exponent) while (i < input.length()) {
                nextSymbol = input[i];
                if (isdigit(nextSymbol)) {
                    decPlace++;
                    dec.push_back((int)nextSymbol - 48); //0 in ASCII is 48
                }
                else if (nextSymbol == '_') {
                    if (i == input.length() - 1 || decPlace == 0) {
                        fail = true;
                        break;
                    }
                }
                else if (i == input.length() - 1 && (nextSymbol == 'f' || nextSymbol == 'F' || nextSymbol == 'd' || nextSymbol == 'D')) {
                    suffix = true;
                }
                else if (nextSymbol == 'e' || nextSymbol == 'E') {
                    exponent = true;
                    i++;
                    break;
                }
                else {
                    fail = true;
                    break;
                }
                i++;
            }
            if (exponent) while (i < input.length()) {
                nextSymbol = input[i];
                if (isdigit(nextSymbol)) {
                    exp.push_back((int)nextSymbol - 48); //0 in ASCII is 48
                }
                else if (expFirst && nextSymbol == '-') {
                    expSign = -1;
                }
                else if (i == input.length() - 1 && (nextSymbol == 'f' || nextSymbol == 'F' || nextSymbol == 'd' || nextSymbol == 'D')) {
                    suffix = true;
                }
                else {
                    fail = true;
                    break;
                }
                expFirst = false;
                i++;
            }
            if ( (!suffix && !exponent && !decimal) ||
                (whole.size() == 0 && dec.size() == 0) ) fail = true;
        }
        else fail = true;

        if (fail) cout << "Invalid Input. Try again.\n\n";
        else {
            cout << "  ";
            for (int i = 0; i < whole.size(); i++) cout << whole[i];
            if (dec.size() > 0) cout << ".";
            for (int i = 0; i < dec.size(); i++) cout << dec[i];
            if (exponent) cout << "e";
            for (int i = 0; i < exp.size(); i++) cout << exp[i];
            cout << "\n\n";
        }
    } while (true);
}

int main() {
    inputNum();
    return 0;
}

/*long double add() {

}

long double subtr() {

}

long double mult() {

}

long double div() {

}*/