#pragma once

class Node {
public:
    Node(int _weight, char _sym, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr) {
        this->weight = _weight;
        this->sym = _sym;
        this->left = left;
        this->right = right;
        this->parent = parent;
    }
    char sym;
    int weight;
    Node* left;
    Node* right;
    Node* parent;

    Node& operator=(Node* rhs) {
        this->left = rhs->left;
        this->right = rhs->right;
        this->sym = rhs->sym;
        this->weight = rhs->weight;
        return *this;
    }

    char getSym() {
        return this->sym;
    }

    void setSym(char _sym) {
        this->sym = _sym;
    }

    int getWeight() {
        return this->weight;
    }

    bool IsLeaf() {
        return (this->left == nullptr) && (this->right == nullptr);
    }
};