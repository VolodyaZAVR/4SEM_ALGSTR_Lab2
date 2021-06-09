#include "Tree.h"

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    while (root != nullptr)
        remove(root->data);
    delete root;
}

bool Tree::contains(int key) {
    Node *current = root;
    while (current != nullptr) {
        if (current->data == key)
            return true;
        else if (current->data > key)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

void Tree::insert(int key) {
    if (root == nullptr)
        root = new Node(key);
    else {
        Node *current = root;
        bool flag = false;
        while (true) {
            if (current->data >= key && current->left != nullptr) {
                current = current->left;
            } else if (current->data >= key && current->left == nullptr) {
                break;
            } else if (current->data < key && current->right != nullptr) {
                current = current->right;
            } else {
                flag = true;
                break;
            }
        }
        if (flag) {
            current->right = new Node(key, nullptr, nullptr, current);
        } else {
            current->left = new Node(key, nullptr, nullptr, current);
        }
    }
}

void Tree::remove(int key) {
    if (root == nullptr)
        throw "Tree is empty!";
    else if (root->left == nullptr && root->right == nullptr && root->data == key) {
        root = nullptr;
        return;
    } else if (root->left == nullptr && root->right == nullptr && root->data != key) {
        throw "There no is this element!";
    } else {
        Node *curr = root;
        Node *curr_child;
        while (curr != nullptr) {
            if (curr->data == key) {
                if (curr->left == nullptr && curr->right == nullptr) {
                    if (curr->parent->left == curr)
                        curr->parent->left = nullptr;
                    else
                        curr->parent->right = nullptr;
                    delete curr;
                } else if (curr->left != nullptr && curr->right == nullptr) {
                    curr_child = curr->left;
                    curr->data = curr_child->data;
                    curr->left = curr_child->left;
                    curr->right = curr_child->right;
                    if (curr->left != nullptr)
                        curr->left->parent = curr;
                    if (curr->right != nullptr)
                        curr->right->parent = curr;
                    delete curr_child;
                } else if (curr->left == nullptr && curr->right != nullptr) {
                    curr_child = curr->right;
                    curr->data = curr_child->data;
                    curr->left = curr_child->left;
                    curr->right = curr_child->right;
                    if (curr->left != nullptr)
                        curr->left->parent = curr;
                    if (curr->right != nullptr)
                        curr->right->parent = curr;
                    delete curr_child;
                } else {
                    curr_child = curr->right;
                    if (curr_child->left == nullptr) {
                        curr->right = curr_child->right;
                        if (curr_child->right != nullptr)
                            curr_child->right->parent = curr;
                    } else {
                        while (curr_child->left != nullptr && curr_child != nullptr)
                            curr_child = curr_child->left;
                        curr_child->parent->left = curr_child->right;
                        if (curr_child->right != nullptr)
                            curr_child->right->parent = curr_child->parent;
                    }
                    curr->data = curr_child->data;
                    delete curr_child;
                }
                return;
            }
            if (curr->data > key)
                curr = curr->left;
            else
                curr = curr->right;
        }
        throw "There is no this element!";
    }
}