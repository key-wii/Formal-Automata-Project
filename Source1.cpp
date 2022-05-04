#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

vector <long double> outputs;
vector <char> operators;
vector <int> priorities;

int getNumLen(string input, int numLength, int start) {
    if (input.find(")", start) != string::npos)
        numLength = input.find(")", start);
    if (input.find("+", start) != string::npos) {
        int temp = input.find("+", start);
        if (temp < numLength) numLength = temp;
    }
    if (input.find("-", start) != string::npos) {
        int temp = input.find("-", start);
        if (temp < numLength) numLength = temp;
    }
    if (input.find("*", start) != string::npos) {
        int temp = input.find("*", start);
        if (temp < numLength) numLength = temp;
    }
    if (input.find("/", start) != string::npos) {
        int temp = input.find("/", start);
        if (temp < numLength) numLength = temp;
    }
    return numLength;
}

void calculate() {
    long double result = 0;
    int len = priorities.size();

    int priorityHigh = 0;
    for (int i = 0; i < len; i++)
        if (priorities[i] > priorityHigh) priorityHigh = priorities[i];

    for (int i = 0; i < len; i++) {
        if () {

        }

        priorityHigh--;
    }


    cout << " = ";
    cout << setprecision(16) << result;
    cout << "\n\n";
}

void inputNum() {
    int priority = 0;
    bool fail = false;
    //infinite loop (until manual exit)
    do {
        outputs.clear();
        operators.clear();
        priorities.clear();
        vector<int> whole;
        vector<int> dec;
        vector<int> exp;

        cout << "Please input a floating point number (or q to quit)\n";
        cout << "> ";
        string input;
        getline(cin, input);
        fail = false;

        int numLength = input.length();
        numLength = getNumLen(input, numLength, 0);

        char prevSymbol;
        char nextSymbol = input[0];
        int index = 1;
        int wholeDigits = 1;

        while (nextSymbol == '(') {
            nextSymbol = input[index];
            index++;
            priority++;
        }

        bool decimal = nextSymbol == '.';
        if (decimal) {
            index++;
            wholeDigits = 0;
        }
        int decPlace = 0;

        bool exponent = false;
        bool expFirst = true;
        int expSign = 1;

        bool suffix = false;

        if (!decimal) whole.push_back((int)nextSymbol - 48); //0 in ASCII is 48
        bool firstNum = true;
        bool lastNum = false;

        do {
            if (lastNum) fail = true; //To prevent (a)(b); Numbers need operator in between
            if (!firstNum) {
                whole.clear();
                dec.clear();
                exp.clear();
            }
            firstNum = false;

            long double full = 0;
            //cout << "index" << index << "\n";

            if (nextSymbol == 'q' || nextSymbol == 'Q') return;
            else if (decimal || isdigit(nextSymbol)) {
                while (index < numLength && !decimal) {
                    prevSymbol = nextSymbol;
                    nextSymbol = input[index];
                    if (isdigit(nextSymbol)) {
                        wholeDigits++;
                        whole.push_back((int)nextSymbol - 48); //0 in ASCII is 48
                    }
                    else if (nextSymbol == '_') {
                        if (index == numLength - 1) {
                            fail = true;
                            break;
                        }
                    }
                    else if (index == numLength - 1 && (nextSymbol == 'f' || nextSymbol == 'F' || nextSymbol == 'd' || nextSymbol == 'D')) {
                        suffix = true;
                    }
                    else if (index != numLength - 1 && (nextSymbol == 'e' || nextSymbol == 'E')) {
                        exponent = true;
                        index++;
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
                    index++;
                }
                if (decimal && !exponent) while (index < numLength) {
                    prevSymbol = nextSymbol;
                    nextSymbol = input[index];
                    if (isdigit(nextSymbol)) {
                        decPlace++;
                        dec.push_back((int)nextSymbol - 48); //0 in ASCII is 48
                    }
                    else if (nextSymbol == '_') {
                        if (index == numLength - 1 || decPlace == 0) {
                            fail = true;
                            break;
                        }
                    }
                    else if (index == numLength - 1 && (nextSymbol == 'f' || nextSymbol == 'F' || nextSymbol == 'd' || nextSymbol == 'D')) {
                        suffix = true;
                    }
                    else if (prevSymbol != '_' && (nextSymbol == 'e' || nextSymbol == 'E')) {
                        exponent = true;
                        index++;
                        break;
                    }
                    else {
                        fail = true;
                        break;
                    }
                    index++;
                }
                if (exponent) while (index < numLength) {
                    nextSymbol = input[index];
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
                    else if (index == numLength - 1 && (nextSymbol == 'f' || nextSymbol == 'F' || nextSymbol == 'd' || nextSymbol == 'D')) {
                        suffix = true;
                    }
                    else {
                        fail = true;
                        break;
                    }
                    expFirst = false;
                    index++;
                }
                if ((!suffix && !exponent && !decimal) ||
                    (whole.size() == 0 && dec.size() == 0)) fail = true;
            }
            else fail = true;

            nextSymbol = input[index];
            while (nextSymbol == ')') {
                index++;
                priority--;
                nextSymbol = input[index];
            }
            if (priority < 0) fail = true;

            if (fail) {
                cout << "Invalid Input. Try again.\n\n";
                break;
            }
            else {
                /*cout << "\n";
                for (int i = 0; i < whole.size(); i++) cout << whole[i];
                if (dec.size() > 0) cout << ".";
                for (int i = 0; i < dec.size(); i++) cout << dec[i];
                if (exponent) cout << "e";
                for (int i = 0; i < exp.size(); i++) cout << exp[i];
                cout << "\n\n";*/

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
                outputs.push_back(full);

                /*cout << "out" << outputs.size() << " ";
                cout << setprecision(16) << full;
                cout << "\n";*/
            }

            if (nextSymbol == '+' || nextSymbol == '-' || nextSymbol == '*' || nextSymbol == '/') {
                operators.push_back(nextSymbol);
                index++;
                nextSymbol = input[index];
                /*cout << "opr" << operators.size() << " ";
                cout << operators[operators.size() - 1];
                cout << "\n";*/
            }
            else lastNum = true;

            //reset values
            wholeDigits = 1;

            while (nextSymbol == '(') {
                nextSymbol = input[index];
                index++;
                priority++;
            }

            decimal = nextSymbol == '.';
            if (decimal) {
                index++;
                wholeDigits = 0;
            }
            decPlace = 0;

            exponent = false;
            expFirst = true;
            expSign = 1;
            suffix = false;

            numLength = input.length();
            numLength = getNumLen(input, numLength, index);
            //cout << "indexEnd" << index << "\n";
        }
        while (index < input.length());

        if (!fail) {
            calculate();
        }
        index = 1;
    } while (true);
}

int main() {
    inputNum();
    return 0;
}