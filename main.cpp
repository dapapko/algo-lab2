#include <iostream>
#include <vector>
#include <string>
#include "Binnum.h"
#include "Stack.h"
using namespace std;
using T = int;


bool isOperator(string &exp) {
    return (exp == "+" || exp == "-" || exp == "x" || exp == "/");
}

Binnum<T> rpnExprCalc(vector<string> &expr) {
    auto *stack = new Stack<Binnum<T>>();
    for (string e: expr) {
        if (!isOperator(e)) {
            try {
                Binnum<T> num = Binnum<T>(stoi(e));
                cout << "Binary representation of operand: ";
                num.prt_bin();
                cout << endl;
                stack->push(num);
            } catch (std::invalid_argument &exc) {
                throw std::invalid_argument("Invalid symbol in expression");
            }
        } else {
            Binnum<T> a = stack->pop();
            Binnum<T> b = stack->pop();
            Binnum<T> r;
            if (e == "+") r = a + b;
            else if (e == "-") r = b - a;
            else if (e == "x") r = a * b;
            stack->push(r);
        }

    }
    Binnum<T> result = stack->pop();
    if (!stack->isEmpty()) {
        throw std::invalid_argument("Invalid expression");
    }
    return result;
}

int main() {
    vector<string> v;
    string s;
    cout << "Enter RPN expression: ";
    while ((cin.peek() != '\n') && (cin.peek() != EOF)) {
        cin >> s;
        v.push_back(s);
    }
    try {
        Binnum<T> result = rpnExprCalc(v);
        cout << "Result: " << result << endl;
        cout << "Result (bin): ";
        result.prt_bin();
        cout << endl;
    } catch (std::exception &e) {
        cout << "Smth is wrong with your expression" << endl;
    }
}