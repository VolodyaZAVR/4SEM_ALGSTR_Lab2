#pragma once
#include "Elem.h"

class List {
private:
	Elem* head;
	int size;
public:
	List();
	~List();
	void push_front(Node*);
	void push_back(Node*);
	void pop_front();
	void insert(Node*, int);
	int get_size();
	bool isEmpty();
	void clear();
	int contains(char);
	Node* operator[] (int);
	void print_to_console();
	List Sort();
};

List::List() {
	size = 0;
	head = nullptr;
}

List::~List() {
	clear();
}

void List::push_front(Node* node) {
	head = new Elem(node, head);
	size++;
}

void List::push_back(Node* node) {
	if (head == nullptr) {
		head = new Elem(node);
	}
	else {
		Elem* cur = head;
		while (cur->next != nullptr) {
			cur = cur->next;
		}
		cur->next = new Elem(node);
	}
	size++;
}

void List::pop_front() {
	Elem* cur = head;
	head = head->next;
	cur->~Elem();
	size--;
}

bool List::isEmpty() {
	return (!size);
}

void List::clear() {
	while (!isEmpty()) {
		pop_front();
	}
}

int List::get_size() {
	return size;
}

Node* List::operator[](int index) {
	int count = 0;
	Elem* cur = head;
	while (cur != nullptr) {
		if (count == index) {
			return cur->node;
		} cur = cur->next;
		count++;
	}
}

int List::contains(char sym) {
	if (isEmpty()) {
		throw "List is empty";
	}
	Elem* cur = head;
	int index = 0;
	while (sym != cur->node->sym && cur->next != nullptr) {
		cur = cur->next;
		index++;
	}
	if (sym == cur->node->sym)
		return index;
	return -1;
}

void List::insert(Node* in, int index) {
	if (index > size || index < 0) {
		throw "Wrong index";
	}
	else if (index == size) {
		push_back(in);
	}
	else if (index == 0) {
		push_front(in);
	}
	else {
		Elem* prev = head;
		for (int i = 0; i < (index - 1); i++) {
			prev = prev->next;
		}
		Elem* newNode = new Elem(in, prev->next);
		prev->next = newNode;
		size++;
	}
}

void List::print_to_console() {
	Elem* curr = head;
	for (int i = 0; i < size; i++) {
		std::cout << curr->node->getSym() << " " << curr->node->getWeight() << " ";
		curr = curr->next;
	}
	std::cout << std::endl;
}

int partition(List& list, int low, int high)
{
	Node* pivot = new Node(list[high]->weight, list[high]->sym, list[high]->left, list[high]->right);
	int i = (low - 1);
	for (int j = low; j < high; j++)
	{
		if (list[j]->weight < pivot->weight)
		{
			i++;
			Node* tmp = new Node(list[j]->weight, list[j]->sym, list[j]->left, list[j]->right);
			*list[j] = list[i];
			*list[i] = *tmp;
		}
	}
	Node* tmp = new Node(list[high]->weight, list[high]->sym, list[high]->left, list[high]->right);
	*list[high] = list[i + 1];
	*list[i + 1] = tmp;
	return i + 1;
}

void Qsort(List& list, int low, int high)
{
	if (low < high)
	{
		int pi = partition(list, low, high);
		Qsort(list, low, pi - 1);
		Qsort(list, pi + 1, high);
	}
}

List List::Sort() {
	List sorted_list = *this;
	Qsort(sorted_list, 0, size - 1);
	return sorted_list;
}
