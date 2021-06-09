#pragma once
#include "Node.h"
#include "Iterator.h"
#include "Stack.h"

class dftIterator : public Iterator {
private:
    Node* current;
    Stack* stack;
public:
    dftIterator(Node* start) {
        stack = new Stack();
        current = start;
        if (current != nullptr) {
            stack->push(current);
        }
        else {
            throw;
        }
    }

    bool has_next() override {
        return !stack->isEmpty();
    }

    Node* next() override {
        if (!has_next())
            throw "There is no more elements!";
        Node* current = stack->pop();
        if (current->right != nullptr)
            stack->push(current->right);
        if (current->left != nullptr)
            stack->push(current->left);
        return current;
    }
};

class Tree {
private:
    Node* root;
public:
    Tree();
    Tree(Node*);
    ~Tree();
    bool contains(char);
    void insert(int, char);
    void remove(char);
    Iterator* create_dft_iterator();
};

Tree::Tree() {
    root = nullptr;
}

Tree::Tree(Node* newRoot) {
    root = newRoot;
}

Tree::~Tree() {
    while (root != nullptr)
        remove(root->sym);
    delete root;
}

Iterator* Tree::create_dft_iterator() {
    return new dftIterator(root);
}

void Tree::insert(int _weight, char _sym) {
    if (root == nullptr)
        root = new Node(_weight, _sym);
    else {
        Node* current = root;
        bool flag = false;
        while (true) {
            if (current->sym >= _sym && current->left != nullptr) {
                current = current->left;
            }
            else if (current->sym >= _sym && current->left == nullptr) {
                break;
            }
            else if (current->sym < _sym && current->right != nullptr) {
                current = current->right;
            }
            else {
                flag = true;
                break;
            }
        }
        if (flag) {
            current->right = new Node(_weight, _sym, nullptr, nullptr, current);
        }
        else {
            current->left = new Node(_weight, _sym, nullptr, nullptr, current);
        }
    }
}

bool Tree::contains(char symbol) {
    Node* current = root;
    while (current != nullptr) {
        if (current->sym == symbol)
            return true;
        else if (current->sym > symbol)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

void Tree::remove(char symbol) {
    if (root == nullptr)
        throw "Tree is empty!";
    else if (root->left == nullptr && root->right == nullptr && root->sym == symbol) {
        root = nullptr;
        return;
    }
    else if (root->left == nullptr && root->right == nullptr && root->sym != symbol) {
        throw "There no is this element!";
    }
    else {
        Node* curr = root;
        Node* curr_child;
        while (curr != nullptr) {
            if (curr->sym == symbol) {
                if (curr->left == nullptr && curr->right == nullptr) {
                    if (curr->parent->left == curr)
                        curr->parent->left = nullptr;
                    else
                        curr->parent->right = nullptr;
                    delete curr;
                }
                else if (curr->left != nullptr && curr->right == nullptr) {
                    curr_child = curr->left;
                    curr->sym = curr_child->sym;
                    curr->left = curr_child->left;
                    curr->right = curr_child->right;
                    if (curr->left != nullptr)
                        curr->left->parent = curr;
                    if (curr->right != nullptr)
                        curr->right->parent = curr;
                    delete curr_child;
                }
                else if (curr->left == nullptr && curr->right != nullptr) {
                    curr_child = curr->right;
                    curr->sym = curr_child->sym;
                    curr->left = curr_child->left;
                    curr->right = curr_child->right;
                    if (curr->left != nullptr)
                        curr->left->parent = curr;
                    if (curr->right != nullptr)
                        curr->right->parent = curr;
                    delete curr_child;
                }
                else {
                    curr_child = curr->right;
                    if (curr_child->left == nullptr) {
                        curr->right = curr_child->right;
                        if (curr_child->right != nullptr)
                            curr_child->right->parent = curr;
                    }
                    else {
                        while (curr_child->left != nullptr && curr_child != nullptr)
                            curr_child = curr_child->left;
                        curr_child->parent->left = curr_child->right;
                        if (curr_child->right != nullptr)
                            curr_child->right->parent = curr_child->parent;
                    }
                    curr->sym = curr_child->sym;
                    delete curr_child;
                }
                return;
            }
            if (curr->sym > symbol)
                curr = curr->left;
            else
                curr = curr->right;
        }
        throw "There is no this element!";
    }
}