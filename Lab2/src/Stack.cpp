#include "Tree.h"

Tree::Stack::Stack() {
    top = nullptr;
}

Tree::Stack::~Stack() {
    while (top != nullptr)
        pop();
    delete top;
}

void Tree::Stack::push(Node *newElem) {
    if (!isEmpty()) {
        top = new StackNode(newElem, top);
    } else {
        top = new StackNode(newElem);
    }
}

Tree::Node *Tree::Stack::pop() {
    Node *temp = top->elem;
    top = top->next;
    return temp;
}

bool Tree::Stack::isEmpty() {
    if (top == nullptr)
        return true;
    else
        return false;
}