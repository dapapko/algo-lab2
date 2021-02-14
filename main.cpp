#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Binnum.h"
#include "Stack.h"
using namespace std;
using T = int;


bool isOperator(string &exp) {
    return (exp == "+" || exp == "-" || exp == "x" || exp == "/" || exp == "(");
}
bool isOperand(string s) {
    try {
        stoi(s);
        return true;
    } catch (std::exception &e) {
        return false;
    }
}
vector<string> infixToRPN(vector<string> expr) {
    map <string, int> ops;
    vector<string> res;
    ops["x"] = 3; ops["/"] = 3;
    ops["+"] = 2; ops["-"] = 2;
    ops["("] = 1;
    Stack<string> result;
    Stack<string> operations;
    for(string value: expr) {
        if (!isOperand(value))
        {

            if (value == ")") {
                while (operations.get_top() != "(")
                {
                    res.push_back(operations.get_top());
                    operations.pop();

                }
                operations.pop();
            }
            else if (value == ")")
            {
                operations.push(value);
            }
            else if (operations.isEmpty() || (ops[operations.get_top()] < ops[value]))
            {
                operations.push(value);
            }
            else
            {
                do
                {
                    res.push_back(operations.pop());
                } while (!(operations.isEmpty() || (ops[operations.get_top()] < ops[value])));
                operations.push(value);
            }
        }
        else
        {
            res.push_back(value);
        }
    }
    while (!operations.isEmpty())
    {
        res.push_back(operations.pop());
    }

    return res;
}

Binnum<T> rpnExprCalc(vector<string> expr) {
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

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "You should specify infix (i) or prefix (p) notation" << endl;
        exit(1);
    }
    char notation = *argv[1];
    string s;
    vector<string> v ;
    cout << "Enter expression: ";
    while ((cin.peek() != '\n') && (cin.peek() != EOF)) {
        cin >> s;
        v.push_back(s);
    }
    try {
        Binnum<T> result;
        if (notation == 'i') result = rpnExprCalc(infixToRPN(v));
        else if (notation == 'p') result = rpnExprCalc(v);
        cout << "Result: " << result << endl;
        cout << "Result (bin): ";
        result.prt_bin();
        cout << endl;
        } catch (std::exception &e) {
             cout << "Smth is wrong with your expression" << endl;
    }


}
