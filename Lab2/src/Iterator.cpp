#include "Tree.h"

Iterator *Tree::create_dft_iterator() {
    return new dftIterator(root);
}

Iterator *Tree::create_bft_iterator() {
    return new bftIterator(root);
}

Tree::dftIterator::dftIterator(Node *start) {
    stack = new Stack();
    stack->push(start);
}

Tree::bftIterator::bftIterator(Node *start) {
    queue = new Queue();
    queue->enqueue(start);
}

bool Tree::dftIterator::has_next() {
    return !stack->isEmpty();
}

bool Tree::bftIterator::has_next() {
    return !queue->isEmpty();
}

int Tree::dftIterator::next() {
    if (!has_next())
        throw "There is no more elements!";
    Node *current = stack->pop();
    if (current->right != nullptr)
        stack->push(current->right);
    if (current->left != nullptr)
        stack->push(current->left);
    return current->data;
}

int Tree::bftIterator::next() {
    if (!has_next())
        throw "There is no more elements!";
    Node *current = queue->dequeue();
    if (current->left != nullptr)
        queue->enqueue(current->left);
    if (current->right != nullptr)
        queue->enqueue(current->right);
    return current->data;
}