#pragma once
#include <string>
#include "List.h"
#include "BST.h"
#include "Char_List.h"

using namespace std;

size_t Find_space(List& list, Node* node) {
	size_t index = 0;
	for (size_t i = 0; i < list.get_size(); i++) {
		if (node->weight >= list[i]->weight) {
			continue;
		}
		else {
			index = i;
			break;
		}
	}
	if (index == 0) {
		index = list.get_size();
	}
	return index;

}

Char_List Find_code_sym(char sym, Char_List* list) {
	size_t len = _msize(list) / sizeof(Char_List);
	for (size_t i = 0; i < len; i++) {
		if (list[i].GetSym() == sym) 
			return list[i];
	}
}

class haffman {
private:
	string input;
	string encodedExpr;
	List nodes;
	Char_List* list;
public:
	haffman();
	~haffman();
	void parser(string);
	List get_nodes();
	Char_List* Encode();
	void print_freq_list();
	void print_char_codes();
	void print_encoded_expr();
	string getDecode();
};

haffman::haffman() {
	nodes = List();
	list = nullptr;
}


haffman::~haffman() {
	nodes.clear();
	delete list;
}

void haffman::parser(string input) {
	if (!input.length()) {
		throw "An empty string cannot be encoded!";
	}
	Node* node = new Node(1, input[0]);
	this->nodes.push_back(node);
	int index;
	for (int i = 1; i < input.length(); i++) {
		index = nodes.contains(input[i]);
		if (index == -1) {
			node = new Node(1, input[i]);
			this->nodes.push_back(node);
		}
		else {
			this->nodes[index]->weight++;
		}
	}
	this->input = input;
	this->nodes = this->nodes.Sort();
}

List haffman::get_nodes() {
	return nodes;
}

Char_List* haffman::Encode() {
	this->list = new Char_List[nodes.get_size()];
	if (nodes.get_size() == 1) {
		list[0].Push_back(1);
		return list;
	}

	while (nodes.get_size() != 1) {
		Node* newNode = new Node(nodes[0]->weight + nodes[1]->weight, ' ', nodes[0], nodes[1]);
		this->nodes[0]->parent = newNode;
		this->nodes[1]->parent = newNode;
		nodes.pop_front();
		nodes.pop_front();
		size_t index_set_node = Find_space(nodes, newNode);
		this->nodes.insert(newNode, index_set_node);
	}

	Tree tree = Tree(nodes[0]);
	Iterator* iter = tree.create_dft_iterator();
	size_t num_of_sym = 0;

	while (iter->has_next()) {
		Node* node = iter->next();
		if (node != nullptr && node->IsLeaf()) {
			this->list[num_of_sym].SetSym(node->sym);

			while (node->parent != nullptr) {
				if (node->parent->left == node) {
					this->list[num_of_sym].Push_front(0);
				}
				else {
					this->list[num_of_sym].Push_front(1);
				}
				node = node->parent;
			}
			num_of_sym++;
		}
	}

	size_t len = _msize(list) / sizeof(Char_List);

	Char_List* new_expr = new Char_List[input.length()];
	for (size_t i = 0; i < input.length(); i++) {
		Char_List code_sym = Find_code_sym(input[i], list);
		for (size_t j = 0; j < code_sym.GetSize(); j++) {
			encodedExpr += char(code_sym[j] + '0');
		}
		new_expr[i] = Char_List(code_sym);
		encodedExpr += ' ';
	}
	return new_expr;
}

void haffman::print_freq_list() {
	if (nodes.get_size() == 0) 
		throw "Nothing is encoded";

	cout << "Table of character frequencies:" << endl;
	for (size_t i = 0; i < nodes.get_size(); i++) {
		cout << nodes[i]->sym << " ";
	}
	cout << endl;

	for (size_t i = 0; i < nodes.get_size(); i++) {
		cout << nodes[i]->weight << " ";
	}

	cout << endl << endl;
}

void haffman::print_char_codes() {
	if (list == nullptr) 
		throw "Nothing is encoded";
	cout << "Char codes:" << endl;
	size_t len = _msize(list) / sizeof(Char_List);

	for (size_t i = 0; i < len; i++) {
		cout << list[i].GetSym() << " - ";
		for (size_t j = 0; j < list[i].GetSize(); j++) {
			cout << char(list[i][j] + '0');
		}
		cout << " ; " << endl;
	}
	cout << endl << endl;
}

void haffman::print_encoded_expr() {
	if (list == nullptr) 
		throw "Nothing is encoded";
	cout << "Encoded expression:" << endl << encodedExpr << endl;
}

string haffman::getDecode() {
	if (list == nullptr)
		throw "Nothing is encoded";
	return encodedExpr;
}