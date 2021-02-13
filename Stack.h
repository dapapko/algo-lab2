//
// Created by drford on 13.02.2021.
//

#ifndef ESE_LAB1_STACK_H
#define ESE_LAB1_STACK_H

#include <stdexcept>

template <typename T>
class Node {
public:
    T value;
    Node *next;
    Node(T val) {
        this->value = val;
        this->next = nullptr;
    }

};

template<typename T>
class Stack {
    Node<T> *top;
public:
    Stack() : top(nullptr) {}

    T get_top() {
        if (top == nullptr) throw std::length_error("Getting head of empty stack");
        return top->value;
    }

    void push(T value) {
        auto *newtop = new Node<T>(value);
        newtop->value = value;
        newtop->next = top;
        top = newtop;
    }

    bool isEmpty() {
        return (top == nullptr);
    }

    T pop() {
        if (isEmpty()) {
            throw std::length_error("Pop from empty stack");
        }
        T temp = top->value;
        Node<T> *pv = top;
        top = top->next;
        delete pv;
        return temp;
    }

    ~Stack() {
        while (top) {
            Node<T> *node = top;
            top = top->next;
            delete node;
        }
    }
};


#endif //ESE_LAB1_STACK_H
