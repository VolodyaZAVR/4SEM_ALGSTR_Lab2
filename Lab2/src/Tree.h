#pragma once

#include "Iterator.h"

class Tree {
private:
    class Node {
    public:
        Node(int data, Node *left = nullptr, Node *right = nullptr, Node *parent = nullptr) {
            this->data = data;
            this->left = left;
            this->right = right;
            this->parent = parent;
        };

        ~Node() = default;;

        int data;
        Node *left;
        Node *right;
        Node *parent;
    };

    Node *root;
public:
    Tree();

    ~Tree();

    bool contains(int); // ����� �������� � ������ �� �����
    void insert(int); // ���������� �������� � ������ �� �����. ������ �������� �� O(logN)
    void remove(int); // �������� �������� ������ �� �����

    Iterator* create_dft_iterator(); // �������� ���������, ������������ ���� �� ������� ������ � ������� (depth-first traverse)

    class Stack {
    private:
        class StackNode {
        public:
            explicit StackNode(Node *elem, StackNode *next = nullptr) {
                this->elem = elem;
                this->next = next;
            }

            ~StackNode() = default;;

            Node *elem;
            StackNode *next;
        };

        StackNode *top;
    public:
        Stack();

        ~Stack();

        void push(Node *);

        Node *pop();

        bool isEmpty();
    };

    class dftIterator : public Iterator {
    private:
        Stack *stack;
    public:
        explicit dftIterator(Node *);

        bool has_next() override;

        int next() override;
    };

    Iterator* create_bft_iterator(); // �������� ���������, ������������ ������ ������ � ������ (breadth-first traverse)

    class Queue {
    private:
        class QueueNode {
        public:
            explicit QueueNode(Node *elem, QueueNode *next = nullptr) {
                this->elem = elem;
                this->next = next;
            }

            ~QueueNode() = default;;

            Node *elem;
            QueueNode *next;

        };

        QueueNode *head;
        QueueNode *tail;
    public:
        Queue();

        ~Queue();

        void enqueue(Node *);

        Node *dequeue();

        bool isEmpty();
    };

    class bftIterator : public Iterator {
    private:
        Queue *queue;
    public:
        explicit bftIterator(Node *);

        bool has_next() override;

        int next() override;
    };
};