#pragma once
#include "Elem.h"

class Stack {
private:
    Elem* top;
public:
    Stack();
    ~Stack();
    void push(Node*);
    Node* pop();
    bool isEmpty();
};

Stack::Stack() {
    top = nullptr;
}

Stack::~Stack() {
    while (top != nullptr)
        pop();
    delete top;
}

void Stack::push(Node* newElem) {
    if (!isEmpty()) {
        top = new Elem(newElem, top);
    }
    else {
        top = new Elem(newElem);
    }
}

Node* Stack::pop() {
    Node* temp = top->node;
    Elem* tmp = top;
    top = top->next;
    tmp->~Elem();
    return temp;
}

bool Stack::isEmpty() {
    if (top == nullptr)
        return true;
    else
        return false;
}