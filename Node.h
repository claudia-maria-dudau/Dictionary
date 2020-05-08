#pragma once
#include <iostream>
#include "KeyComp.h"
using namespace std;

template <typename K, typename V, typename KeyComp> class Dictionary;

//clasa pentru noduri
template <typename K, typename V>
class Node {
	K key;
	V value;
	string color;
	Node* left, * right, * parent;

public:
	Node(K&, V&);	
	void swapColor(Node<K, V>*);

	friend class Dictionary<K, V, KeyComp<K>>;
};

//constructor cu parametrii
template <typename K, typename V>
inline Node<K, V>::Node(K& k, V& v) : key(k), value(v), color("red"), left(NULL), right(NULL), parent(NULL) {}

template<typename K, typename V>
void Node<K, V>::swapColor(Node<K, V>* node) {
	string culAux = this->color;
	this->color = node->color;
	node->color = culAux;
}
