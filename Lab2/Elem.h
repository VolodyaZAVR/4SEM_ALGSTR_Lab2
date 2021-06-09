#pragma once
#include "Node.h"

class Elem {
public:
	Elem(Node* node, Elem* next = nullptr) {
		this->node = node;
		this->next = next;
	}
	~Elem() {};
	Node* node;
	Elem* next;
};