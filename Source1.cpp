#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

vector <long double> output;
vector <long double> operators;
vector <int> priorities;

void inputNum() {
    string input;
    vector<int> whole;
    vector<int> dec;
    vector<int> exp;
    int priority = 0;
    do {
        whole.clear();
        dec.clear();
        exp.clear();
        long double full = 0;

        cout << "Please input a floating point number (or q to quit)\n";
        cout << "> ";
        getline(cin, input);

        int numLength = input.length();
        if (input.find(" ") != string::npos)
            numLength = input.find(" ");;
        if (input.find(")") != string::npos) {
            int temp = input.find(")");
            if (temp < numLength) numLength = temp;
        }

        int i = 1;
        char prevSymbol;
        char nextSymbol = input[0];
        int wholeDigits = 1;

        while (nextSymbol == '(') {
            i++;
            priority++;
            nextSymbol = input[i - 1];
        }

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
            while (i < numLength && !decimal) {
                prevSymbol = nextSymbol;
                nextSymbol = input[i];
                if (isdigit(nextSymbol)) {
                    wholeDigits++;
                    whole.push_back((int)nextSymbol - 48); //0 in ASCII is 48
                }
                else if (nextSymbol == '_') {
                    if (i == numLength - 1) {
                        fail = true;
                        break;
                    }
                }
                else if (i == numLength - 1 && (nextSymbol == 'f' || nextSymbol == 'F' || nextSymbol == 'd' || nextSymbol == 'D')) {
                    suffix = true;
                }
                else if (i != numLength - 1 && (nextSymbol == 'e' || nextSymbol == 'E')) {
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
            if (decimal && !exponent) while (i < numLength) {
                prevSymbol = nextSymbol;
                nextSymbol = input[i];
                if (isdigit(nextSymbol)) {
                    decPlace++;
                    dec.push_back((int)nextSymbol - 48); //0 in ASCII is 48
                }
                else if (nextSymbol == '_') {
                    if (i == numLength - 1 || decPlace == 0) {
                        fail = true;
                        break;
                    }
                }
                else if (i == numLength - 1 && (nextSymbol == 'f' || nextSymbol == 'F' || nextSymbol == 'd' || nextSymbol == 'D')) {
                    suffix = true;
                }
                else if (prevSymbol != '_' && (nextSymbol == 'e' || nextSymbol == 'E')) {
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
            if (exponent) while (i < numLength) {
                nextSymbol = input[i];
                if (isdigit(nextSymbol)) {
                    exp.push_back((int)nextSymbol - 48); //0 in ASCII is 48
                }
                else if (expFirst) {
                    if (prevSymbol == '_') {
                        fail = true;
                        return;
                    }
                    if (nextSymbol == '-')
                        expSign = -1;
                }
                else if (i == numLength - 1 && (nextSymbol == 'f' || nextSymbol == 'F' || nextSymbol == 'd' || nextSymbol == 'D')) {
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

        nextSymbol = input[i];
        while (nextSymbol == ')') {
            i++;
            priority--;
            nextSymbol = input[i];
        }
        if (priority < 0) fail = true;

        if (fail) cout << "Invalid Input. Try again.\n\n";
        else {
            /*cout << "  ";
            for (int i = 0; i < whole.size(); i++) cout << whole[i];
            if (dec.size() > 0) cout << ".";
            for (int i = 0; i < dec.size(); i++) cout << dec[i];
            if (exponent) cout << "e";
            for (int i = 0; i < exp.size(); i++) cout << exp[i];*/

            int j = 0;
            for (int i = whole.size() - 1; i >= 0; i--) {
                full += whole[i] * pow(10, j);
                j++;
            }
            for (int i = 0; i < dec.size(); i++)
                full += dec[i] * pow(10, (-i - 1));
            j = 0;
            long double expPart = 0;
            for (int i = exp.size() - 1; i >= 0; i--) {
                expPart += exp[i] * pow(10, j);
                j++;
            }
            full = full * pow(10, expPart * expSign);
            output.push_back(full);

            cout << " = ";
            cout << setprecision(16) << full;
            cout << "\n\n";
        }
    } while (true);
}

int main() {
    inputNum();
    return 0;
}