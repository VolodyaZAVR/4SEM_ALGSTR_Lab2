#pragma once
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "list.h"
#include "RB_Tree.h"

using namespace std;

class haffmanTree {
private:
	class haffmanNode {
	public:
		haffmanNode* _left;
		haffmanNode* _right;
		haffmanNode* _parent;
		string _code;
		char _value;
		haffmanNode(char value, haffmanNode* parent, haffmanNode* left, haffmanNode* right) {
			this->_value = value;
			this->_code = "";
			this->_parent = parent;
			this->_left = left;
			this->_right = right;
		}
		~haffmanNode() {};
	};

	int _power;
	haffmanNode* _root;
public:
	haffmanTree(char value, int power) {
		_power = power;
		_root = new haffmanNode(value, nullptr, nullptr, nullptr);
	}

	haffmanTree(haffmanTree* leftTree, haffmanTree* rightTree) {
		_power = leftTree->_power + rightTree->_power;
		_root = new haffmanNode(NULL, nullptr, leftTree->_root, rightTree->_root);
		_root->_left->_parent = _root;
		_root->_right->_parent = _root;
	}

	void toRbTree(RB_Tree<char, string>* tree, haffmanNode* node)
	{
		if (node != nullptr) {
			if (node->_right != nullptr) {
				toRbTree(tree, node->_right);
			}
			if (node->_left != nullptr) {
				toRbTree(tree, node->_left);
			}
			if (node->_value != 0)
				tree->insert(node->_value, node->_code);
		}
	}

	void RLK(haffmanNode* node)
	{
		if (node != nullptr) {
			if (node->_right != nullptr) {
				node->_right->_code = node->_code + "1";
				RLK(node->_right);
			}
			if (node->_left != nullptr) {
				node->_left->_code = node->_code + "0";
				RLK(node->_left);
			}
		}
	}
};