#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

vector <long double> outputs;
vector <char> operators;
vector <int> priorities;
vector <int> parentheses;

//Debug function
void printVecs() {
    cout << "nums: ";
    for (int i = 0; i < outputs.size(); i++)
        cout << outputs[i] << " ";
    cout << "\n";
    cout << "math:  ";
    for (int i = 0; i < operators.size(); i++)
        cout << operators[i] << " ";
    cout << "\n";
    /*cout << "pris: ";
    for (int i = 0; i < priorities.size(); i++)
        cout << priorities[i] << " ";
    cout << "\n";
    cout << "pare: ";
    for (int i = 0; i < parentheses.size(); i++)
        cout << parentheses[i] << " ";
    cout << "\n";*/
}

void setResult(int i, long double result) {
    outputs[i - 1] = result;
    outputs.erase(outputs.begin() + i); //erases i'th element
    priorities.erase(priorities.begin() + i); //erases i'th element
    parentheses.erase(parentheses.begin() + i); //erases i'th element
    operators.erase(operators.begin() + i - 1); //erases i-1'th element
    //printVecs(); //DEBUG
}

void calculate() {
    long double result = outputs[outputs.size() - 1];
    //printVecs(); //DEBUG

    int priorityHigh = 0;
    for (int i = 0; i < priorities.size(); i++)
        if (priorities[i] > priorityHigh) priorityHigh = priorities[i];
    int parenthesesHigh = 0;
    for (int i = 0; i < parentheses.size(); i++)
        if (parentheses[i] > parenthesesHigh) parenthesesHigh = parentheses[i];

    bool parenth = false;
    bool addSubtract = false;

    for (int i = 1; i < outputs.size(); i++) {
        if (priorities[i] == priorityHigh && parentheses[i - 1] == parentheses[i] && priorities[i - 1] == priorities[i]) {
            if (addSubtract) {
                switch (operators[i - 1]) {
                    case '+':
                        result = outputs[i - 1] + outputs[i];
                        //cout << outputs[i - 1] << " + " << outputs[i] << " = " << result << "\n"; //DEBUG
                        setResult(i, result);
                        i--;
                        break;
                    case '-':
                        result = outputs[i - 1] - outputs[i];
                        //cout << outputs[i - 1] << " - " << outputs[i] << " = " << result << "\n"; //DEBUG
                        setResult(i, result);
                        i--;
                        break;
                }
            } else {
                switch (operators[i - 1]) {
                    case '*':
                        result = outputs[i - 1] * outputs[i];
                        //cout << outputs[i - 1] << " * " << outputs[i] << " = " << result << "\n"; //DEBUG
                        setResult(i, result);
                        i--;
                        break;
                    case '/':
                        result = outputs[i - 1] / outputs[i];
                        //cout << outputs[i - 1] << " / " << outputs[i] << " = " << result << "\n"; //DEBUG
                        setResult(i, result);
                        i--;
                        break;
                }
            }
        }
        if (i == outputs.size() - 1) {
            if (addSubtract) {
                if (priorityHigh > 0 && priorityHigh >= parenthesesHigh) {
                    for (int i = 0; i < priorities.size(); i++)
                        if (priorities[i] == priorityHigh) priorities[i] = priorityHigh - 1;
                    priorityHigh--;
                }
                if (parenthesesHigh > 0 && parenthesesHigh >= priorityHigh) {
                    for (int i = 0; i < parentheses.size(); i++)
                        if (parentheses[i] == parenthesesHigh) parentheses[i] = parenthesesHigh - 1;
                    parenthesesHigh--;
                }
            }
            addSubtract = !addSubtract;
            i = 0; //i++ will set i = 1
        }
    }
    // (1f+1f)-(2f*2f)
    // = -2
    // 5.0*(12.0*(1.0-1.0)+3.0)+100.0+((9.0e1f))-8.0e1d
    // = 125
    // 5.0*(12.0*(1.0-1.0)+3.0)+100.0+((9.0e+1f))-8.0e1d
    // = 45

    cout << " = ";
    cout << setprecision(16) << result;
    cout << "\n\n";
}

int getNumLen(string input, int numLength, int start) {
    int ePos = -99; //arbitrary int because string positions will never be -99
    if (input.find("e", start) != string::npos)
        ePos = input.find("e", start);
    //cout << "ePos" << ePos <<"\n"; DEBUG

    if (input.find(")", start) != string::npos)
        numLength = input.find(")", start);
    if (input.find("+", start) != string::npos) {
        int temp = input.find("+", start);
        if (ePos != -99 && temp - 1 == ePos) {
            int tempStart = temp + 1;
            temp = input.find("+", tempStart);
            //DEBUG
            /*cout << "+ after e\n";
            cout << "temp " << temp << "\n";
            cout << "tempStart " << tempStart << "\n";*/
        }
        if (temp < numLength && temp > 0) numLength = temp;
    }
    if (input.find("-", start) != string::npos) {
        int temp = input.find("-", start);
        if (ePos != 9999 && temp - 1 == ePos) {
            int tempStart = temp + 1;
            temp = input.find("-", tempStart);
            //DEBUG
            /*cout << "- after e\n";
            cout << "temp " << temp << "\n";
            cout << "tempStart " << tempStart << "\n";*/
        }
        if (temp < numLength && temp > 0) numLength = temp;
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

void inputNum() {
    bool fail = false;
    //infinite loop (until manual exit)
    do {
        outputs.clear();
        operators.clear();
        priorities.clear();
        parentheses.clear();
        vector<int> whole;
        vector<int> dec;
        vector<int> exp;
        int priority = 0;
        int paren = 0;

        cout << "Please input a floating point expression without spaces (or q to quit)\n";
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
            paren++;
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
            //cout << "index" << index << "\n"; //DEBUG

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

            priorities.push_back(priority);
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
                //DEBUG
                /*cout << "\n";
                for (int i = 0; i < whole.size(); i++) cout << whole[i];
                if (dec.size() > 0) cout << ".";
                for (int i = 0; i < dec.size(); i++) cout << dec[i];
                if (exponent) cout << "e";
                for (int i = 0; i < exp.size(); i++) cout << exp[i];
                cout << "\n";*/

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
                parentheses.push_back(paren);

                //DEBUG
                /*cout << "out" << outputs.size() << " ";
                cout << setprecision(16) << full;
                cout << "\n";*/
            }

            if (nextSymbol == '+' || nextSymbol == '-' || nextSymbol == '*' || nextSymbol == '/') {
                operators.push_back(nextSymbol);
                index++;
                nextSymbol = input[index];
                //DEBUG
                /*cout << "opr" << operators.size() << " ";
                cout << operators[operators.size() - 1];
                cout << "\n";*/
            }
            else lastNum = true;

            //reset values
            wholeDigits = 1;

            while (nextSymbol == '(') {
                //nextSymbol = input[index]; //DEBUG
                index++;
                priority++;
                paren++;
                nextSymbol = input[index];
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
            //cout << "indexEnd" << index << "\n"; //DEBUG
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