#pragma once
#include<bitset>

using namespace std;

class Char_List {
public:
    Char_List();

    void Pop_Front();
    void Clear();
    void Push_back(uint8_t bit);
    void Push_front(uint8_t bit);
    void Pop_back();
    void Print_to_console();
    size_t GetSize();
    bool IsEmpty();
    uint8_t& operator[] (size_t index);
    void Remove(size_t index);
    void SetSym(char sym);
    char GetSym();
private:

    class List_Node {
    public:
        List_Node* pnext;
        uint8_t bit;
        List_Node(uint8_t bit, List_Node* pNext = nullptr) {
            this->bit = bit;
            this->pnext = pNext;
        }
    };
    size_t size;
    List_Node* head;
    char sym;
};

Char_List::Char_List() {
    size = 0;
    head = nullptr;

}

void Char_List::SetSym(char sym) {
    this->sym = sym;
}

char Char_List::GetSym() {
    return this->sym;
}

void Char_List::Pop_back() {
    List_Node* cur = head;
    while (cur->pnext != nullptr) {
        cur = cur->pnext;
    }
    delete cur;
    size--;
}

void Char_List::Pop_Front()
{
    List_Node* tmp = head;
    head = head->pnext;
    delete tmp;
    size--;
}

void Char_List::Push_front(uint8_t bit) {
    head = new List_Node(bit, head);
    size++;

}
void Char_List::Clear()
{
    while (size > 0) {
        Pop_Front();
    }
}

void Char_List::Push_back(uint8_t bit)
{
    if (head == nullptr) {
        head = new List_Node(bit);
    }
    else {
        List_Node* cur = head;
        while (cur->pnext != nullptr) {
            cur = cur->pnext;
        }
        cur->pnext = new List_Node(bit);
    }
    size++;
}

size_t Char_List::GetSize()
{
    return size;
}



uint8_t& Char_List::operator[](size_t index)
{
    int count = 0;
    List_Node* cur = head;
    while (cur != nullptr) {
        if (count == index) {
            return cur->bit;
        } cur = cur->pnext;
        count++;
    }
}

void Char_List::Print_to_console() {
    List_Node* cur = head;
    for (size_t i = 0; i < size; i++) {
        cout << cur->bit << " ";
        cur = cur->pnext;
    }
    cout << "\n";
}

bool Char_List::IsEmpty() {

    return size == 0;
}



void Char_List::Remove(size_t index) {
    if (index > size - 1) {
        throw "Wrong index\n";
    }
    if (index == 0) {
        Pop_Front();
    }
    else if (index == size - 1) {
        Pop_back();
    }
    else {
        List_Node* cur = head;
        size_t i = 0;
        while (cur != nullptr) {
            if (index == i - 1) {
                List_Node* tmp = cur->pnext;
                cur->pnext = tmp->pnext;
                delete tmp;
                break;
            }
            i++;
            cur = cur->pnext;
        }
    }
}