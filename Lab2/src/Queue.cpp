#include "Tree.h"

Tree::Queue::Queue() {
    head = nullptr;
    tail = nullptr;
}

Tree::Queue::~Queue() {
    while (head != nullptr)
        dequeue();
    delete head;
}

void Tree::Queue::enqueue(Node *newElem) {
    if (!isEmpty()) {
        tail->next = new QueueNode(newElem);
        tail = tail->next;
    } else {
        head = new QueueNode(newElem);
        tail = head;
    }
}

Tree::Node *Tree::Queue::dequeue() {
    Node *ans = head->elem;
    head = head->next;
    return ans;
}

bool Tree::Queue::isEmpty() {
    if (head == nullptr)
        return true;
    else
        return false;
}