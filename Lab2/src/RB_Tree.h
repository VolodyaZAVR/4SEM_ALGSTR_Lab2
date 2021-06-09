#pragma once
#include <iostream>
#include "list.h"

using namespace std;

template<class T_key, class T_value>
class RB_Tree {
private:
    class Node {
    public:
        Node(T_key key, T_value value, Node* leftChild = nullptr, Node* rightChild = nullptr, Node* parent = nullptr,
             bool color = true) { // Red color = true, black = false
            this->key = key;
            this->value = value;
            this->leftChild = leftChild;
            this->rightChild = rightChild;
            this->parent = parent;
            this->color = color;
        };

        ~Node() {};

        T_key key;
        T_value value;
        Node* leftChild;
        Node* rightChild;
        Node* parent;
        bool color;
    };

    Node* root;
    Node* nil;
public:
    RB_Tree() { // constructor
        nil = new Node(' ', ' ', nullptr, nullptr, nullptr,
            false); // this link is needed to combine all links to the missing element
        root = nil;
    }

    ~RB_Tree() { //deconstructor
        clear();
        root = nullptr;
        nil = nullptr;
    }

    void left_rotate(Node* x) {
        Node* y;
        Node* p;
        if (x->rightChild == nil) {
            return;
        }
        else {
            y = x->rightChild;
            p = x->parent;
            if (y->leftChild != nil) {
                x->rightChild = y->leftChild;
                x->rightChild->parent = x;
            }
            else
                x->rightChild = nil;
            if (x->parent == nullptr) {
                y->parent = nullptr;
                root = y;
            }
            else if (p->leftChild == x) {
                p->leftChild = y;
                y->parent = p;
            }
            else {
                p->rightChild = y;
                y->parent = p;
            }
            x->parent = y;
            y->leftChild = x;
        }
    }

    void right_rotate(Node* y) {
        Node* x;
        Node* p;
        if (y->leftChild == nil) {
            return;
        }
        else {
            x = y->leftChild;
            p = y->parent;
            if (x->rightChild != nil) {
                y->leftChild = x->rightChild;
                x->rightChild->parent = y;
            }
            else
                y->leftChild = nil;
            if (y->parent == nullptr) {
                root = x;
                x->parent = nullptr;
            }
            else if (y == p->rightChild) {
                p->rightChild = x;
                x->parent = p;
            }
            else {
                p->leftChild = x;
                x->parent = p;
            }
            x->rightChild = y;
            y->parent = x;
        }
    }

    void insert(T_key key, T_value value) {
        Node* current;
        Node* newNode;
        bool to_right;
        if (key == ' ') {
            throw "Key error: the key cannot have the given value";
        }
        newNode = new Node(key, value, nil, nil); // create new node
        if (root == nil) {
            root = newNode;
            root->color = false; //repaint root color in black
        }
        else {
            to_right = false; //set value for right child as false
            current = root;
            while (true) { // run for a tree to find a leaf for insert
                if (newNode->key > current->key && current->rightChild != nil) {
                    current = current->rightChild;
                }
                else if (newNode->key <= current->key && current->leftChild != nil) {
                    current = current->leftChild;
                }
                else if (newNode->key <= current->key && current->leftChild == nil) {
                    break;
                }
                else {
                    to_right = true;
                    break;
                }
            }
            if (to_right) { // set a new node as a right child
                current->rightChild = newNode;
            }
            else { // set a new node as a left child
                current->leftChild = newNode;
            }
            newNode->parent = current;
            recover_tree_insert(newNode); // call method for recover tree properties
        }
    }

    void recover_tree_insert(Node* newNode) {
        Node* p; //parent
        Node* grandParent;
        if (newNode == nil) {
            throw "Unexpected node recieved";
        }
        else {
            p = newNode->parent;
            grandParent = p->parent;
            while (p->color && p) { // the algorithm is executed while the color of the node is red
                if (p == grandParent->leftChild) {
                    // case 1
                    if (grandParent->rightChild->color) {
                        grandParent->leftChild->color = false;
                        grandParent->rightChild->color = false;
                        grandParent->color = true;
                        newNode = grandParent;
                    }
                    else {
                        // case 2
                        if (newNode == p->rightChild) {
                            newNode = p;
                            left_rotate(newNode);
                        }
                        // case 3
                        p->color = false;
                        grandParent->color = true;
                        right_rotate(grandParent);
                    }
                }
                else {
                    // case 1
                    if (grandParent->leftChild->color) {
                        grandParent->leftChild->color = false;
                        grandParent->rightChild->color = false;
                        grandParent->color = true;
                        newNode = grandParent;
                    }
                    else {
                        // case 2
                        if (newNode == p->leftChild) {
                            newNode = p;
                            right_rotate(newNode);
                        }
                        // case 3
                        p->color = false;
                        grandParent->color = true;
                        left_rotate(grandParent);
                    }
                }
                root->color = false;
            }
        }
    }

    Node* find(T_key key) {
        Node* current = root;
        while (current != nil) {
            if (current->key == key)
                return current;
            else if (current->key > key)
                current = current->leftChild;
            else current = current->rightChild;
        }
        return nullptr;
    }
    T_value find_value(T_key key) {
        Node* current = root;
        while (current != nil) {
            if (current->key == key)
                return current->value;
            else if (current->key > key)
                current = current->leftChild;
            else current = current->rightChild;
        }
        return NULL;
    }

    void remove(T_key key) {
        Node* nodeToBeDeleted;
        Node* min;
        Node* x;
        bool originalColor;
        nodeToBeDeleted = find(key); // looking for an node to delete by key
        if (nodeToBeDeleted) { // if the search was successful
            originalColor = nodeToBeDeleted->color; // Store the nodeToBeDeleted color to origrinalColor
            if (nodeToBeDeleted->leftChild == nil) { // if left child of nodeToBeDeleted is nil
                x = nodeToBeDeleted->rightChild; // then swap nodeToBeDeleted with right child
                if (nodeToBeDeleted->parent == nullptr) {
                    root = nodeToBeDeleted->rightChild;
                }
                else if (nodeToBeDeleted == nodeToBeDeleted->parent->leftChild) {
                    nodeToBeDeleted->parent->leftChild = nodeToBeDeleted->rightChild;
                }
                else {
                    nodeToBeDeleted->parent->rightChild = nodeToBeDeleted->rightChild;
                }
                nodeToBeDeleted->rightChild->parent = nodeToBeDeleted->parent;
            }
            else if (nodeToBeDeleted->rightChild == nil) { // if right child of nodeToBeDeleted is nil
                x = nodeToBeDeleted->leftChild; // then swap nodeToBeDeleted with left child
                if (nodeToBeDeleted->parent == nullptr) {
                    root = nodeToBeDeleted->leftChild;
                }
                else if (nodeToBeDeleted == nodeToBeDeleted->parent->leftChild) {
                    nodeToBeDeleted->parent->leftChild = nodeToBeDeleted->leftChild;
                }
                else {
                    nodeToBeDeleted->parent->rightChild = nodeToBeDeleted->leftChild;
                }
                nodeToBeDeleted->leftChild->parent = nodeToBeDeleted->parent;
            }
            else {
                min = nodeToBeDeleted->rightChild; // assign the minimum of right subtree of noteToBeDeleted into min
                while (min->leftChild != nil)
                    min = min->leftChild;
                originalColor = min->color; // save the color of min in originalColor
                x = min->rightChild; // assign the rightChild of min into x
                if (min->parent == nodeToBeDeleted) { // if y is a child of nodeToBeDeleted 
                    x->parent = min; // then set the parent of x as min
                }
                else { // else, transplant min with rightChild of min
                    if (min->parent == nullptr) {
                        root = min->rightChild;
                    }
                    else if (min == min->parent->leftChild) {
                        min->parent->leftChild = min->rightChild;
                    }
                    else {
                        min->parent->rightChild = min->rightChild;
                    }
                    min->rightChild->parent = min->parent;
                    min->rightChild = nodeToBeDeleted->rightChild;
                    min->rightChild->parent = min;
                }
                // transplant nodeToBeDeleted with min
                if (nodeToBeDeleted->parent == nullptr) {
                    root = min;
                }
                else if (nodeToBeDeleted == nodeToBeDeleted->parent->leftChild) {
                    nodeToBeDeleted->parent->leftChild = min;
                }
                else {
                    nodeToBeDeleted->parent->rightChild = min;
                }
                min->parent = nodeToBeDeleted->parent;
                min->leftChild = nodeToBeDeleted->leftChild;
                min->leftChild->parent = min;
                min->color = nodeToBeDeleted->color; // set the color of min with originalColor
            }
            delete nodeToBeDeleted;
            if (!originalColor) { // calling the recovery algorithm if a node with black color has been deleted
                recover_tree_remove(x);
            }
        }
        else {
            throw "There is no such element!";
        }
    }

    void recover_tree_remove(Node* x) {
        Node* w;
        while (x != root && !x->color) {
            if (x->parent->leftChild == x) {
                w = x->parent->rightChild;
                // Case 1
                if (w->color) {
                    w->color = false;
                    x->parent->color = true;
                    left_rotate(x->parent);
                    w = x->parent->rightChild;
                }
                // Case 2
                if (w->leftChild->color == false && w->rightChild->color == false) {
                    w->color = true;
                    x = x->parent;
                }
                // Case 3
                else if (w->rightChild->color == false) {
                    w->leftChild->color = false;
                    w->color = true;
                    right_rotate(w);
                    w = x->parent->rightChild;
                }
                else {
                    // Case 4
                    w->color = x->parent->color;
                    x->parent->color = false;
                    w->rightChild->color = false;
                    left_rotate(x->parent);
                    x = root;
                }
            }
            else {
                w = x->parent->leftChild;
                // Case 1
                if (w->color == true) {
                    w->color = false;
                    x->parent->color = true;
                    right_rotate(x->parent);
                    w = x->parent->leftChild;
                }
                // Case 2
                if (w->leftChild->color == false && w->rightChild->color == false) {
                    w->color = true;
                    x = x->parent;
                }
                // Case 3
                else if (w->leftChild->color == false) {
                    w->rightChild->color = false;
                    w->color = true;
                    left_rotate(w);
                    w = x->parent->leftChild;
                }
                // Case 4
                else {
                    w->color = x->parent->color;
                    x->parent->color = false;
                    w->leftChild->color = false;
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = false;
        root->color = false;
    }

    void clear() {
        while (root != nil)
            remove(root->key);
    }

    List<T_key> get_keys() {
        List<T_key> keys;
        Node* current = root;
        get_next_key(&keys, current);
        return keys;
    }

    void get_next_key(List<T_key>* keys, Node* current) {
        if (current != nil) {
            keys->push_back(current->key);
            get_next_key(&*keys, current->leftChild);
            get_next_key(&*keys, current->rightChild);
        }
    }

    List<T_value> get_values() {
        List<T_value> values;
        Node* current = root;
        get_next_value(&values, current);
        return values;
    }

    void get_next_value(List<T_value>* values, Node* current) {
        if (current != nil) {
            values->push_back(current->value);
            get_next_value(&*values, current->leftChild);
            get_next_value(&*values, current->rightChild);
        }
    }

    void print(Node* current = nullptr) {
        if (root != nil) {
            if (current == nullptr)
                current = root;
            cout << "Key: " << current->key << " |Value: " << current->value << " |Color: ";
            if (current->color)
                cout << "Red";
            else
                cout << "Black";
            if (!current->parent)
                cout << " |Parent: No";
            else
                cout << " |Parent: " << current->parent->key;
            if (current->leftChild == nil)
                cout << " |Left : nil";
            else
                cout << " |Left : " << current->leftChild->key;
            if (current->rightChild == nil)
                cout << " |Right : nil";
            else
                cout << " |Right : " << current->rightChild->key;
            cout << endl;
            if (current->leftChild != nil)
                print(current->leftChild);
            if (current->rightChild != nil)
                print(current->rightChild);
        }
        else
            cout << "Tree is empty" << endl;
    }
};
