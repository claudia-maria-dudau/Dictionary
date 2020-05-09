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
	Node(const K&, const V&);
	void swapColor(Node<K, V>*);

	K getKey();
	V getValue();
	Node<K, V>* getLeft();
	Node<K, V>* getRight();

	friend class Dictionary<K, V, KeyComp<K>>;
};

//constructor cu parametrii
template <typename K, typename V>
inline Node<K, V>::Node(const K& k, const V& v) : key(k), value(v), color("red"), left(NULL), right(NULL), parent(NULL) {}

//schimbare culori intre 2 noduri
template<typename K, typename V>
void Node<K, V>::swapColor(Node<K, V>* node) {
	string culAux = this->color;
	this->color = node->color;
	node->color = culAux;
}

//obtinere cheie
template<typename K, typename V>
K Node<K, V>::getKey() {
	return this->key;
}

//obtinere valoare
template<typename K, typename V>
V Node<K, V>::getValue() {
	return this->value;
}

//obtinere fiu stang
template<typename K, typename V>
Node<K, V>* Node<K, V>::getLeft() {
	return this->left;
}

//obtinere fiu drept
template<typename K, typename V>
Node<K, V>* Node<K, V>::getRight() {
	return this->right;
}