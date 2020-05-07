#pragma once
#include "Dictionary.h"
#include <iostream>
using namespace std;

template <typename K, typename V, typename F> class Dictionary;

//clasa pentru noduri
template <typename K, typename V>
class Node {
	K key;
	V value;
	string color;
	Node* left, * right, * parent;

public:
	Node(K&, V&);	
	void recolorare();

	friend class Dictionary<K, V, F>;
};

//constructor cu parametrii
template <typename K, typename V>
inline Node<K, V>::Node(K& k, V& v) : key(k), value(v), color("red"), left(NULL), right(NULL), parent(NULL) {}

//metoda pentru recolorarea unui nod
template<typename K, typename V>
void Node<K, V>::recolorare() {
	if (this->color == "red")
		this->color = "black";
	else
		this->color = "red";
}
