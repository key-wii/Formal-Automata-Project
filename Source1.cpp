#include <iostream>
#include <iomanip>
#include <string>
#include<stdio.h>
#include<ctype.h>
#include <vector>
#include "input.h"
using namespace std;

vector<vector <int>> inputNum() {
    string input;
    vector<int> whole;
    vector<int> dec;
    vector<vector <int>> full;
    do {
        whole.clear();
        dec.clear();
        full.clear();

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
        long double expPart = 0;

        bool output = true;
        if (nextSymbol == 'q' || nextSymbol == 'Q') return full;
        else if (decimal || isdigit(nextSymbol)) {
            whole.push_back((int)nextSymbol - 48); //0 in ASCII is 48
            while (i < input.length() && !decimal) {
                prevSymbol = nextSymbol;
                nextSymbol = input[i];
                if (isdigit(nextSymbol)) {
                    wholeDigits++;
                    whole.push_back((int)nextSymbol - 48); //0 in ASCII is 48
                }
                else if (nextSymbol == '_') {
                    if (i == input.length() - 1) {
                        cout << "Invalid Input. Try again.\n\n";
                        output = false;
                        break;
                    }
                }
                else if (i == input.length() - 1 && (nextSymbol == 'f' || nextSymbol == 'F' || nextSymbol == 'd' || nextSymbol == 'D')) {
                    //do nothing
                }
                else if (i != input.length() - 1 && (nextSymbol == 'e' || nextSymbol == 'E')) {
                    exponent = true;
                    i++;
                    break;
                }
                else if (nextSymbol == '.') {
                    if (prevSymbol == '_') {
                        cout << "Invalid Input. Try again.\n\n";
                        output = false;
                        break;
                    }
                    else decimal = true;
                }
                else {
                    cout << "Invalid Input. Try again.\n\n";
                    output = false;
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
                        cout << "Invalid Input. Try again.\n\n";
                        output = false;
                        break;
                    }
                }
                else if (i == input.length() - 1 && (nextSymbol == 'f' || nextSymbol == 'F' || nextSymbol == 'd' || nextSymbol == 'D')) {
                    //do nothing
                }
                else if (nextSymbol == 'e' || nextSymbol == 'E') {
                    exponent = true;
                    break;
                }
                else {
                    cout << "Invalid Input. Try again.\n\n";
                    output = false;
                    break;
                }
                i++;
            }
            if (exponent) while (i < input.length()) {
                nextSymbol = input[i];
                if (isdigit(nextSymbol)) {
                    expPart *= 10;
                    expPart += (double)nextSymbol - 48; //0 in ASCII is 48
                }
                else {
                    cout << "Invalid Input. Try again.\n\n";
                    output = false;
                    break;
                }
                i++;
            }
            if (dec.size() == 0) {
                cout << "Invalid Input. Try again.\n\n";
                output = false;
            }
        }
        else {
            cout << "Invalid Input. Try again.\n\n";
            output = false;
        }
        if (output) {
            cout << "  ";
            for (int i = 0; i < whole.size(); i++) cout << whole[i];
            cout << ".";
            for (int i = 0; i < dec.size(); i++) cout << dec[i];
            if (exponent) cout << "e" << setprecision(20) << expPart;
            cout << "\n\n";
        }
    } while (true);
    full.push_back(whole);
    full.push_back(dec);
    return full;
}

int main() {
    vector<vector <int>> num = inputNum();

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